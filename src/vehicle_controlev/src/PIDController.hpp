#ifndef VEHICLECONTROLTERMINAL_PIDCONTROLLER_H
#define VEHICLECONTROLTERMINAL_PIDCONTROLLER_H
#include <iostream>

class PIDController {
private:
    const static int Ti = 30;
    double sumError;
    double dError;
    int count;
public:

	double errors[Ti];

    /* Controller gains */
    float Kp = 0.0;
    float Ki = 0.0;
    float Kd = 0.0;

    /* Derivative low-pass filter time constant */
    float tau = 0.01;

    /* Output limits */
    float limMin = 0;
    float limMax = 200;
    
    /* Integrator limits */
    float limMinInt = -50;
    float limMaxInt = 200;

    /* Sample time (in seconds) */
    float T = 0.02f;

    /* Controller "memory" */
    float integrator = 0.0f;
    float prevError = 0.0f;			/* Required for integrator */
    float differentiator = 0.0f;
    float prevMeasurement = 0.0f;		/* Required for differentiator */

    /* Controller output */
    float out;
    
    PIDController():Kp(20),Ki(50),Kd(0),sumError(0),dError(0),count(0) {
        ClearErrors();
    }
    PIDController(double kp_, double ki_, double kd_, double limMax_, double limMin_, double limMaxInt_, double limMinInt_) {
        Kp = kp_;
        Ki = ki_;
        Kd = kd_;
        limMax = limMax_;
        limMin = limMin_;
        limMaxInt = limMaxInt_;
        limMinInt = limMinInt_;

        ClearErrors();
    }
    ~PIDController() {
    }
    double GetDError() {
        return dError;
    }
    double GetSumError() {
        return sumError;
    }
    void PushErrors(double error) {
        sumError = sumError + error - errors[0];
        count++;
        if (count >= 2) {
            dError = error - errors[Ti - 1];
        }
        for (int i = 0; i < Ti - 1; i++) {
            errors[i] = errors[i + 1];
        }
        errors[Ti - 1] = error;
    }
    void ClearErrors() {
        sumError = 0;
        dError = 0;
        count = 0;
        for (int i = 0; i < Ti; i++) {
            errors[i] = 0;
        }

        /* Clear controller variables */
        integrator = 0.0f;
        prevError  = 0.0f;

        differentiator  = 0.0f;
        prevMeasurement = 0.0f;

        out = 0.0f;
    }
    void Result() {
        out = Kp*errors[Ti - 1] + Ki*sumError + Kd*dError;
    }

    float Update(float target, float measurement) {

        /*
        * Error signal
        */
        float error = target - measurement;


        /*
        * Proportional
        */
        float proportional = Kp * error;


        /*
        * Integral
        */
        integrator = integrator + 0.5f * Ki * T * (error + prevError);

        /* Anti-wind-up via integrator clamping */
        if (integrator > limMaxInt) {

            integrator = limMaxInt;

        } else if (integrator < limMinInt) {

            integrator = limMinInt;

        }


        /*
        * Derivative (band-limited differentiator)
        */
            
        differentiator = -(2.0f * Kd * (measurement - prevMeasurement)	/* Note: derivative on measurement, therefore minus sign in front of equation! */
                            + (2.0f * tau - T) * differentiator)
                            / (2.0f * tau + T);


        /*
        * Compute output and apply limits
        */
        out = (proportional + integrator + differentiator);
        std::cout <<proportional <<"\t"<<integrator <<"\t"<<differentiator <<"\n";

        if (out > limMax) {

            out = limMax;

        } else if (out < limMin) {

            out = limMin;

        }

        /* Store error and measurement for later use */
        prevError       = error;
        prevMeasurement = measurement;

        /* Return controller output */
        return out;        
    }

};
#endif //VEHICLECONTROLTERMINAL_PIDCONTROLLER_H
