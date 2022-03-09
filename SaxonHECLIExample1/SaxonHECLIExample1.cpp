#include "pch.h"

using namespace System;
using namespace System::IO;
using namespace Saxon::Api;

int main(array<System::String ^> ^args)
{
    Processor^ processor = gcnew Processor();

    Console::WriteLine(processor->ProductVersion);

    DocumentBuilder^ docBuilder = processor->NewDocumentBuilder();

    Uri^ baseUri = gcnew Uri(System::Environment::CurrentDirectory + "\\");

    XdmNode^ inputDoc = docBuilder->Build(gcnew Uri(baseUri, "input-sample1.xml"));

    XsltCompiler^ xsltCompiler = processor->NewXsltCompiler();

    xsltCompiler->BaseUri = baseUri;

    XsltExecutable^ xsltExecutable = xsltCompiler->Compile(gcnew Uri(baseUri, "sheet1.xsl"));

    Xslt30Transformer^ xslt30Transformer = xsltExecutable->Load30();

    FileStream^ resultStream = File::OpenWrite("result1.xml");

    xslt30Transformer->ApplyTemplates(inputDoc, processor->NewSerializer(resultStream));

    resultStream->Close();

    return 0;
}
