// AbstractFactory.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <Windows.h>
#include <iostream>
#include <sysinfoapi.h>

using namespace std;

#define HPUX "HPUX"
#define SUNOS "SunOS"

//#define prototype
//#define product
#define upgrade_product

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

#if defined(product)
class Product {
public :
    virtual ~Product() = 0;
};

Product::~Product() {}

class HPScanner : public Product {};
class HPParser : public Product {};
class HPCodeGenerator : public Product {};
class HPOptimizer : public Product {};
class HPErrorHandler : public Product {};

class SunScanner : public Product {};
class SunParser : public Product {};
class SunCodeGenerator : public Product {};
class SunOptimizer : public Product {};
class SunErrorHandler : public Product {};

class CompilerFactory {
public:
    virtual Product* CreateProduct(int type) = 0;
};

#define SCANNER 1
#define PARSER 2
#define CODEGENERATOR 3
#define OPTIMIZER 4
#define ERRORHANDLER 5

class HPCompilerFactory : public CompilerFactory {
public :
    Product* CreateProduct(int type) {
        switch (type) {
            case SCANNER: return new HPScanner;
            case PARSER: return new HPParser;
            case CODEGENERATOR: return new HPCodeGenerator;
            case OPTIMIZER: return new HPOptimizer;
            case ERRORHANDLER: return new HPErrorHandler;
        }
    }
};

class SunCompilerFactory : public CompilerFactory {
public:
    Product* CreateProduct(int type) {
        switch (type) {
        case SCANNER: return new SunScanner;
        case PARSER: return new SunParser;
        case CODEGENERATOR: return new SunCodeGenerator;
        case OPTIMIZER: return new SunOptimizer;
        case ERRORHANDLER: return new SunErrorHandler;
        }
    }
};

#endif

#if defined(upgrade_product)

class Product {
public :
    virtual Product* Clone() = 0;
};

class HPScanner : public Product {
public:
    Product* Clone() { return new HPScanner(*this); }
};

class HPParser : public Product {
public:
    Product* Clone() { return new HPParser(*this); }
};

class HPCodeGenerator : public Product {
public:
    Product* Clone() { return new HPCodeGenerator(*this); }
};

class HPOptimizer : public Product {
public:
    Product* Clone() { return new HPOptimizer(*this); }
};

class SunScanner : public Product {
public:
    Product* Clone() { return new SunScanner(*this); }
};

class SunParser : public Product {
public:
    Product* Clone() { return new SunParser(*this); }
};

class SunCodeGenerator : public Product {
public:
    Product* Clone() { return new SunCodeGenerator(*this); }
};

class SunOptimizer : public Product {
public:
    Product* Clone() { return new SunOptimizer(*this); }
};

class HPErrorHandler : public Product {
public :
    Product* Clone() { return new HPErrorHandler(*this); }
};

class SunErrorHandler : public Product {
public:
    Product* Clone() { return new SunErrorHandler(*this); }
};

class CompilerFactory {
public :
    virtual Product* CreateProduct(Product* p) = 0;
};

class HPCompilerFactory : public CompilerFactory {
public :
    Product* CreateProduct(Product* p) {
        return p->Clone();
    }
};

class SunCompilerFactory : public CompilerFactory {
public:
    Product* CreateProduct(Product* p) {
        return p->Clone();
    }
};

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

#ifdef product

    pFactory = new HPCompilerFactory;
    //pFactory = new SunCompilerFactory;

    Product* pScanner = pFactory->CreateProduct(SCANNER);
    Product* pParser = pFactory->CreateProduct(PARSER);
    Product* pCodeGenerator = pFactory->CreateProduct(CODEGENERATOR);
    Product* pOptimizer = pFactory->CreateProduct(OPTIMIZER);
    //Product* pErrorHandler = pFactory->CreateProduct(ERRORHANDLER);

#endif

#ifdef upgrade_product
    Product* pScanner, * pParser, * pCodeGenerator, * pOptimizer;
    Product* pErrorHandler;

    pScanner = new HPScanner;
    pParser = new HPParser;
    pCodeGenerator = new HPCodeGenerator;
    pOptimizer = new HPOptimizer;
    pErrorHandler = new HPErrorHandler;

    pFactory = new HPCompilerFactory;

    //pScanner = new SunScanner;
    //pParser = new SunParser;
    //pCodeGenerator = new SunCodeGenerator;
    //pOptimizer = new SunOptimizer;
    //pErrorHandler = new SunErrorHandler;

    //pFactory = new SunCompilerFactory;

    Product* pNewScanner = pFactory->CreateProduct(pScanner);
    Product* pNewParser = pFactory->CreateProduct(pParser);
    Product* pNewCodeGenerator = pFactory->CreateProduct(pCodeGenerator);
    Product* pNewOptimizer = pFactory->CreateProduct(pOptimizer);
    Product* pNewErrorHandler = pFactory->CreateProduct(pErrorHandler);

#endif

}

