# GeistOS

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=JetBrains+Mono&size=24&duration=2800&pause=800&color=58A6FF&center=true&vCenter=true&width=700&lines=GeistOS;Terminal-based+Operating+System;Minimal+by+design;Built+for+clarity+and+control" alt="Typing animation" />
</p>

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=transparent&height=1"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/status-in%20development-1f6feb?style=flat-square">
  <img src="https://img.shields.io/badge/interface-terminal-30363d?style=flat-square">
  <img src="https://img.shields.io/badge/platform-windows-1f6feb?style=flat-square">
  <img src="https://img.shields.io/badge/design-minimal-3fb950?style=flat-square">
  <img src="https://img.shields.io/badge/License-GPLv3-yellow.svg?style=flat-square">
</p>

---

## GeistOS

A minimal, terminal-based operating system focused on clarity, control, and simplicity.

Instead of recreating the complexity of modern systems, GeistOS strips everything down to the essentials.  
The result is an environment that remains readable, predictable, and easy to extend.

---

## Core Principles

- Simplicity over abstraction  
- Full transparency of system behavior  
- Minimal footprint  
- Direct interaction through the terminal  

---

## Features

- Command-line driven system  
- Lightweight architecture  
- Modular structure  
- Easily extendable commands  
- No graphical dependencies  

### GeistScript
  - self-made Programming Language
  - Build into the GeistOS Terminal
  - simple to understand Interpreter

Example Geistscript code with all of it's Features. <br>
This is a simple Example just to show it's capabilities. <br>
More Information about GeistScript in the [GeistScript Wiki](https://github.com/Geistvk/GeistOS/wiki/GeistScript) page

```javascript
const testNum = 50;
let x = 10 * 2;
let result = x + testNum + 30;
let msg = "Hello GeistScript";

result++;

while (x <= 30) {
    if (x <= 24) {
        print("x: " + x + " is <= 24");
    } else if (x > 24 && x <= 27) {
        print("x: " + x + " is > 24 and <= 27");
    } else {
        print("x: " + x + " is > 27");
    }
    x++;
}

//This is a single Line Comment

for (let i = 0; i <= 20; i++) {
    if (((i + 1) % 2) == 0) {
        print("i: " + i);
    } else {
        print("i is Even");
    }
}

/*
This is a multiline comment
This Text will be ignored by the Interpreter
*/

print(msg);
print(result);

function add(a, b) {
     return a + b;
}

function testWorld(name, age) {
    const userData = name + " " + age;
    print(name + " " + age);
    print(userData);
}

function HelloWorld() {
    const userName = "User";
    let testSuccessfull = "Hello World";
    print(testSuccessfull);

    testWorld(userName, 25);

    function yesNo() {
        print("YesNo Func Executed");
    }

    yesNo();
}

const sum = add(5, 10);
print(sum);         //This is the same
print(add(5, 10));  //This is the same

HelloWorld();
```

---

## Quick Start

```bash
git clone https://github.com/Geistvk/GeistOS.git
cd GeistOS
g++ GeistOS.cpp
```

---

## Project Layout

```
GeistOS/
│
├── UIElements              # GUI framework
├── include.zip             # all Dependencies
├── VariadicTable.h         # lib for Ascii Tables
├── lib.cpp                 # lib for large Ascii
├── exampleGeistScript.txt  # example GeistScript code
└── GeistOS.cpp             # entry point
```

## Expandability

Adding new commands is simple and requires only two small steps.

### 1. Create your command function

```cpp
void commandFunction(const std::vector<std::string>& args, Terminal& term) {
    // This function is executed when "yourCommandName" is entered

    // TODO: Add your custom logic here
    std::cout << "Your command executed successfully!" << std::endl;
}
```

### 2. Register the command in `CommandManager`

Add the following snippet at the end of the `command` vector in the `CommandManager` class:

```cpp
{"yourCommandName", [this](const auto& args, const std::string& input){
    (void)input;
    commandFunction(args, terminal);
    return "Command Run Successfull";
    }, 
    {
        false,  // User needs read rights
        false,  // User needs write rights
        false,  // User needs execute rights
        false   // User needs sudo rights
    }
}
```

Now you just need to type "yourCommandName" in the OS in the Terminal and it will execute the function.

---

**Tip:** Keep your command logic modular by placing each command in its own function or file as your project grows.

---

## Design Approach

GeistOS is built with a strict focus on readability.

Every component is written to be understood without digging through layers of abstraction.  
There are no hidden mechanisms and no unnecessary complexity.

The system is intentionally small so that the entire codebase can be explored and modified without friction.

---

## Contributing

Contributions are open.

If you have ideas, improvements, or fixes, feel free to open an issue or submit a pull request.

---

## License

This project is licensed under the [GNU General Public License v3.0](LICENSE).

## Author

Developed by [**Geistvk**](https://github.com/Geistvk)
---

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:0d1117,100:1f6feb&height=120&section=footer"/>
</p>
