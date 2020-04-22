# MINI JAVA COMPILER
## Running The Compiler
This comiler was initially made on a linux os, thus other OSes were not considered whn thinking of how it would be run.
If on linux:
- Ensure you have the `g++` compiler for cpp
    - if not, follow the instructions on how to install it on your linux distribution
- run the below commands:
```bash
# this compiles all the code
g++ utilities/*.cpp language_cfg/*.cpp lexer/*.cpp parser/*.cpp code_gen/*.cpp -o main
# run the compiler
./main
```
## INTRODUCTION
This was part of a project to create a mini Java compiler that is able to generate intermediate code for translation to machine code from code that follows the Java syntax.
The compiler mainly consists of four main parts:
1. The mini java language CFG
2. The Lexer - analyses raw code written and generates Tokens and a symbol table that are then passed on to the next process
3. THe Parser - this created a parse tree of the code written based on the Tokens and SymbolTable passed on to it.
4. The CodeGenerator - this generates intermediate three step code from the parse tree of the class declaration handed to it.
### DISCLAIMER
This compiler only handles (as per the time this documentation was made) the following parts of the Java language:
1. Package declaration
2. Import declarations
3. Class declaration
    1. Class variable declarations
    2. Function declarations
        1. variable declarations
        2. if-else statements
        3. while loops
        4. function calls
        5. complex mathematical operations
# The CFG
This contains a map of the acceptable terminals and non-terminals in the MiniJava language.
This is a basic map with the words used to describe each non-terminal.
These words are very important as they are used through out the compilation process to identify valid Nodes based on the name of the node and whether or not it is a __terminal__ or a __non-terminal__.
The CFG also houses functions that are used to determine valid strings of non-terminals such as __word__
* see `~/language_cfg/language_cfg.cpp` for more
# The Lexer
## Token Handling
This is the component of the compiler that scans through single characters in the source_code to generate valid tokens in the language. It also generates __type__ errors and __invalid token__ progression errors found while the process is going on.
In the event of a valid token being identifies:
* A Node is created to house the token and a name given to it based on which part of the Lexer is unpacking the source code. eg:
```c++
    RESPECTIVE_NODE->add_children(Node(false, "type_defined", "int"));
```
The ablove code adds a child token of type `type_defined` (see the CFG code and look up type_defined to get more insight) a with `value` of `"int"` to the parent token `RESPECTIVE_NODE`. 
* After the source code is all tokenised, all the respective tokens gathered are passed onto the `TokenStream` class as follows:
```c++
TOKEN_STREAM<< RESPECTIVE_NODE
```
The above code adds the the `RESPECTIVE_NODE`(of type `Node`) to the `TOKEN_STREAM` (of type `TokenStream`). See `~/lexer/token_stream.cpp` for more insight on how the `TokenStream` class works.
* see `~/lexer/` for more
## Error Handling
Error handling is done the `ErrorStream` class (see `~/lexer/error_stream.cpp` to get more insight). This class is able to keep tab of lines by the Lexer reporting any new line found.
```c++
ERROR_STREAM->new_line();
```
The above line of code increments the line number to enable accurate reporting of errors pushed to the `ErrorStream` class.
In the event of an error being spotted, a relevant error message is created and pushed to the `ErrorStream` class. e.g
```c++
ERROR_STREAM<< error_message;
```
This `error_message`(of type `std::string`) is added to the `ERROR_MESSAGE` (of type `ErrorStream`) stream and will be displayed on the line the errorStream line_count is at at that respective adding.
* see `~/lexer/error_stream.cpp` for more
## Symbol Table
The symbol table keeps track of variables initialised in the the source code and addes them to a table of reference to be used for type checking and scope checking (this has not yet been implemented).
eg.
```c++
SYMBOL_TABLE->add("myVar", "int", "main");
```
The above code shows a variable `myVar` of type `int` in the scope `main`(function) added to the SYMBOL_TABLE.
* see `~/utilities/symbol_table.cpp` for more
## Function Table
The function table keeps track of the functions found in the source code with their parameter details and return types.
* see `~/utilities/function_table.cpp` for more
## Package Table
The package table keeps track of the packages found in the MiniJava source code.
* see `~/utilities/package_table.cpp` for more
# The Parser
This class takes in the `TokenStream` and `SymbolTable` from the `Lexer` and processes them to create a parse tree displayed on the terminal to show the procession of terminals and non-terminals in the code as followed by the rules declared in the `CFG`.
The creation of the parse tree is done by the `Parser::visit_tree()` function.
```c++
    Parser mini_java_parser(TOKEN_STREAM, SYMBOL_TABLE);
    // creates a tree or the next token in the token progression
    mini_java_parser.visit_tree(TOKEN_STREAM->next_token);
```
* see `~/parser/parser.cpp` for more
# The Code Generator
This class is used to create three step code based on the parse tree passed on to it through the `TokenStream` class altered by the `Parser` class.
The main parts of the `CodeGenerator` are:
1. `ICG::CodeGenerator` - this is the class that is used to generate the three step code
2. `ICG::postfix_it()` - this is the method used to turn an infix equation `Node` into a postif equation `Node` to eable accurate unpacking of the mathematical equation to ensure accurate results.
* for more information on `ICG::postfix_it(Node)` method see: `~/code_gen/postfix_it.h`
## ICG::CodeGenerator
This method takes in the `SymbolTable` and the `TokenStream` (altered TokenStream that is turned into a `ParseTree`) and visits the nodes turning the code into three step processes that will be eassier to turn into assembly code.
example code generated after running:
```c++
ICG::CodeGenerator(SYMBOL_TABLE, TOKEN_STREAM).run();
```
Result:
```python
main(term_0) {
    term_1 = int0
    term_3 = int0 * int20
    term_2 = term_3 + int91
    term_4 = int45 * int87
    term_2 = term_2 + term_4
    term_2 = term_2 + int2
    term_5 = undefined == term_2 
    if(term_5) {
        goto: func_0
    }
    term_8 = int134
}
secondFunction(term_9, term_10) {
    term_11 = int0
    term_12 = int2
    term_13 = undefined == term_12 
    term_14 = term_12 == term_11 
    term_15 = term_13 && term_14
    if(term_15) {
        goto: func_1
    }
    term_18 = float1.0
}
func_0:
    term_7 = int201 + int1

func_1:
    term_17 = int2 / int1
```
* see `~/code_gen/` for more

## __~sloppie__
