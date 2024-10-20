#ifndef __XmlDomDocument_h__
#define __XmlDomDocument_h__

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <string>

using namespace xercesc;

class XmlDomDocument
{
  DOMDocument* m_doc;

public:
  XmlDomDocument(const char* xmlfile);
  ~XmlDomDocument();

  std::string getChildValue(const char* parentTag, int parentIndex, const char* childTag, int childIndex);
  std::string getChildAttribute(const char* parentTag, int parentIndex, const char* childTag, int childIndex,
                                const char* attributeTag);
  int getRootElementCount(const char* rootElementTag);
  int getChildCount(const char* parentTag, int parentIndex, const char* childTag);

private:
  XmlDomDocument();
  XmlDomDocument(const XmlDomDocument&);
};

#endif