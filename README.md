# Todos App in C++
A console todo app :pushpin: written in C++ with file and DB persistence.
#### Build the project
```bash
g++ -o todo main.cpp --std c++17 
```
#### Following commands are supported, after issuing a command, one or more prompts asking user for information may be triggered:

##### Shows help and list of commands
```bash
todo
```
##### Create a new todo
```bash
todo create
```
##### List all todos
```bash
todo list
```
##### Get a single todo
```bash
todo get
```
##### Edit todo title
```bash
todo edit
```
##### Delete todo
```bash
todo delete
```
##### Mark a todo checked or completed
```bash
todo check
```
##### Mark a todo unchecked or pending
```bash
todo uncheck
```

##### Sample `todo list` output. Don't mind the actual text here :smile:
![Sample todo list output](https://github.com/ShahidYousuf/cpp_todos/blob/master/sample_list_output.png)
