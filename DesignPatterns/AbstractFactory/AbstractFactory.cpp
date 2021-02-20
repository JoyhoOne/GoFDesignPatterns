// AbstractFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <sysinfoapi.h>

using namespace std;

#define HPUX "HPUX"
#define SUNOS "SunOS"

#define prototype

#if defined(general) || defined(singleton)
class Scanner {
public :
    virtual ~Scanner() = 0;
};

class Parser {
public:
    virtual ~Parser() = 0;
};

class CodeGenerator {
public:
    virtual ~CodeGenerator() = 0;
};

class Optimizer {
public:
    virtual ~Optimizer() = 0;
};

Scanner::~Scanner() {}
Parser::~Parser() {}
CodeGenerator::~CodeGenerator() {}
Optimizer::~Optimizer() {}

class HPScanner : public Scanner {};
class HPParser : public Parser {};
class HPCodeGenerator : public CodeGenerator {};
class HPOptimizer : public Optimizer {};

class SunScanner : public Scanner {};
class SunParser : public Parser {};
class SunCodeGenerator : public CodeGenerator {};
class SunOptimizer : public Optimizer {};
#endif

#if defined(prototype)
class Scanner {
public:
    virtual Scanner* Clone() = 0;
};

class Parser {
public:
    virtual Parser* Clone() = 0;
};

class CodeGenerator {
public:
    virtual CodeGenerator* Clone() = 0;
};

class Optimizer {
public:
    virtual Optimizer* Clone() = 0;
};

class HPScanner : public Scanner 
{
public:
    Scanner* Clone() { return new HPScanner(*this); }
};

class HPParser : public Parser 
{
public:
    Parser* Clone() { return new HPParser(*this); }
};

class HPCodeGenerator : public CodeGenerator 
{
public:
    CodeGenerator* Clone() { return new HPCodeGenerator(*this); }
};
class HPOptimizer : public Optimizer 
{
public:
    Optimizer* Clone() { return new HPOptimizer(*this); }
};

class SunScanner : public Scanner
{
public:
    Scanner* Clone() { return new SunScanner(*this); }
};

class SunParser : public Parser
{
public:
    Parser* Clone() { return new SunParser(*this); }
};

class SunCodeGenerator : public CodeGenerator
{
public:
    CodeGenerator* Clone() { return new SunCodeGenerator(*this); }
};
class SunOptimizer : public Optimizer
{
public:
    Optimizer* Clone() { return new SunOptimizer(*this); }
};

class CompilerFactory {
public:
    CompilerFactory(Scanner* pScanner, Parser* pParser, CodeGenerator* pCodeGenerator, Optimizer* pOptimizer)
        : pScanner_(pScanner), pParser_(pParser), pCodeGenerator_(pCodeGenerator), pOptimizer_(pOptimizer){}

    Scanner* CreateScanner() { return pScanner_->Clone(); }
    Parser* CreateParser() { return pParser_->Clone(); }
    CodeGenerator* CreateCodeGenerator() { return pCodeGenerator_->Clone(); }
    Optimizer* CreateOptimizer() { return pOptimizer_->Clone(); }
private:
    Scanner* pScanner_;
    Parser* pParser_;
    CodeGenerator* pCodeGenerator_;
    Optimizer* pOptimizer_;
};

#endif

#ifdef general
class CompilerFactory {
public:
    virtual Scanner* CreateScanner() = 0;
    virtual Parser* CreateParser() = 0;
    virtual CodeGenerator* CreateCodeGenerator() = 0;
    virtual Optimizer* CreateOptimizer() = 0;
};

class HPCompilerFactory : public CompilerFactory {
    Scanner* CreateScanner() { new HPScanner; }
    Parser* CreateParser() { new HPParser; }
    CodeGenerator* CreateCodeGenerator() { new HPCodeGenerator; }
    Optimizer* CreateOptimizer() { new HPOptimizer; }
};

class SunCompilerFactory : public CompilerFactory {
    Scanner* CreateScanner() { new SunScanner; }
    Parser* CreateParser() { new SunParser; }
    CodeGenerator* CreateCodeGenerator() { new SunCodeGenerator; }
    Optimizer* CreateOptimizer() { new SunOptimizer; }
};
#endif

#ifdef singleton
class CompilerFactory {
public :
    virtual Scanner* CreateScanner() = 0;
    virtual Parser* CreateParser() = 0;
    virtual CodeGenerator* CreateCodeGeneraotr() = 0;
    virtual Optimizer* CreateOptimizer() = 0;
protected:
    CompilerFactory() {}
    CompilerFactory(const CompilerFactory& rhs);

    static CompilerFactory* pInstance_;
};

class HPCompilerFactory : public CompilerFactory {
public:
    static HPCompilerFactory* CreateInstance() 
    {
        if (pInstance_ == 0)
            pInstance_ = new HPCompilerFactory;

        return (HPCompilerFactory*)pInstance_;
    }

    Scanner* CreateScanner() { new HPScanner; }
    Parser* CreateParser() { new HPParser; }
    CodeGenerator* CreateCodeGenerator() { new HPCodeGenerator; }
    Optimizer* CreateOptimizer() { new HPOptimizer; }

protected:

    HPCompilerFactory() {}
    HPCompilerFactory(const HPCompilerFactory& rhs);
};


CompilerFactory* CompilerFactory::pInstance_ = 0;
#endif

CompilerFactory* pFactory;

int main()
{
    SYSTEM_INFO lpSysInfo;
    GetSystemInfo(&lpSysInfo);
    DWORD dwProcType = lpSysInfo.dwProcessorType;

#ifdef general
    pFactory = new HPCompilerFactory;
    //pFactory = new SunCompilerFactory;

    Scanner* pScanner = pFactory->CreateScanner();
    Parser* pParaser = pFactory->CreateParser();
    CodeGenerator* pCodeGeneratory = pFactory->CreateCodeGenerator();
    Optimizer* pOptimizer = pFactory->CreateOptimizer();
#endif

#ifdef prototype
    HPScanner scanner;
    HPParser parser;
    HPCodeGenerator codeGenerator;
    HPOptimizer optimizer;

    //SunScanner scanner;
    //SunParser parser;
    //SunCodeGenerator codeGenerator;
    //SunOptimizer optimizer;

    pFactory = new CompilerFactory(&scanner, &parser, &codeGenerator, &optimizer);

    Scanner* pScanner = pFactory->CreateScanner();
    Parser* pParaser = pFactory->CreateParser();
    CodeGenerator* pCodeGeneratory = pFactory->CreateCodeGenerator();
    Optimizer* pOptimizer = pFactory->CreateOptimizer();
#endif

}

