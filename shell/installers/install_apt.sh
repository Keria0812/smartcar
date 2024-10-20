# 安装基础的apt包
while true; do
    read -r -p "1. install basic apt package?  [Y/n] " input
    case $input in
        [yY][eE][sS] | [yY] | "")
            sudo apt-get update
            sudo apt-get install -y \
                apt-utils \
                bash-completion \
                build-essential \
                ca-certificates \
                cmake \
                curl \
                expect \
                git \
                libx11-dev \
                locales \
                lsb-core \
                net-tools \
                openssh-server \
                software-properties-common \
                wget \

            ;;

        [nN][oO] | [nN])
            break
            ;;

        *)
            echo "Invalid input..."
            ;;
    esac
done
