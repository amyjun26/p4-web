# p4-web
Introduction
Build a web server for an office hours queue.

The learning goals of this project include Container ADTs, Dynamic Memory, The Big Three, Linked Lists, and Iterators. You will gain experience with new and delete, constructors and destructors, and the list data structure.

When you’re done, you’ll have a working web application accessible through your browser.



Web app background
When you browse to a web site like our EECS 280 office hours queue http://eecsoh.org, your computer makes a request and a server returns a response.



Simple web pages
Your web browser makes a request when you visit a page. First, it connects to the eecsoh.org server, then requests the /index.html page (“no filename” is a shortcut for index.html).

GET / HTTP/1.1
The eecsoh.org server responds with plain text in HTML format. Your browser renders the HTML, adding colors, formatting and images.

HTTP/1.1 200 OK

<html>
  <body>
    EECS Office Hours
    ...
  </body>
</html>

HTTP
HTTP is the protocol that describes what requests and responses should look like. Both are plain text sent from one computer to another computer through the internet. Let’s take a second look at the previous example in more detail.

The request contains an action (GET), a path (/eecsoh/), a version (HTTP/1.1) and some headers (Host: localhost). Headers are key/value pairs separated by a colon.

GET /eecsoh/ HTTP/1.1
Host: localhost

The response contains a version (HTTP/1.1), a status code (200), status description (OK), some headers (Content-Type ... and Content-Length ...), and a body (<html> ... </html>).

HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 3316

<html>
  <body>
    EECS Office Hours
    ...
  </body>
</html>

Web 2.0 applications
Web 2.0 applications like the EECS 280 office hours queue interact with the user. Let’s take a look at what happens when you click the “Sign Up” button.



First, the client’s web browser sends an HTTP request to the server. The request might look like this. Notice that the request includes a body with the information entered by the client. The information is in a machine-readable format called JSON.

POST /api/queue/tail/ HTTP/1.1
Host: localhost
Content-Type: application/json; charset=utf-8
Content-Length: 59

{
    "uniqname": "awdeorio",
    "location": "2705 BBB"
}

Next, the server receives the request sent by the client. The server acts on the request.

Deserialize the JSON data, converting it into a data structure
Modify an internal data structure, possibly a list
Create a response data structure
Serialize the response data structure, converting it to JSON
Send the response to the client
The response to the client might look like this.

HTTP/1.1 201 Created
Content-Type: application/json; charset=utf-8
Content-Length: 78

{
    "location": "2705 BBB",
    "position": 1,
    "uniqname": "awdeorio"
}

Finally, the client receives the response and updates the web page, showing the up-to-date queue in this example.

A server that responds to requests with data instead of HTML is called a REST API (REpresentational State Transfer). REST APIs return data in a machine-readable format like JSON.

Our tutorial Working with JSON provides many more details about the JSON format.

Setup
Set up your visual debugger and version control, then submit to the autograder.

Visual debugger
During setup, name your project p4-web. Use this starter files link: https://eecs280staff.github.io/p4-web/starter-files.tar.gz

VS Code	Visual Studio	Xcode
If you created a main.cpp while following the setup tutorial, rename it to api.cpp. Otherwise, create a new file api.cpp. You should end up with a folder with starter files that look like this. You may have already renamed files like List.hpp.starter to List.hpp.

$ ls
List.hpp                public_error01.in           test03.in
List_compile_check.cpp  public_error01.out.correct  test03.out.correct
List_public_test.cpp    server.py                   test04.in
List_tests.cpp          test01.in                   test04.out.correct
Makefile                test01.out.correct          test05.in
index.html              test02.in                   test05.out.correct
json.hpp                test02.out.correct          unit_test_framework.hpp

Here’s a short description of each starter file.

File(s)	Description
List.hpp.starter	Starter code for the List.
List_tests.cpp	Your List unit tests.
List_compile_check.cpp	Compile check test for List
List_public_test.cpp	A very small test case for List.
test01.in
test01.out.correct
test02.in
test02.out.correct
test03.in
test03.out.correct
test04.in
test04.out.correct
test05.in
test05.out.correct	Simple test cases for the server program.
Makefile	Helper commands for building.
json.hpp	Library for working with JSON.
unit_test_framework.hpp	A simple unit-testing framework.
server.py	Python wrapper script for running the office hours queue server.
index.html	HTML for the office hours queue.
Version control
Set up version control using the Version control tutorial.

After you’re done, you should have a local repository with a “clean” status and your local repository should be connected to a remote GitHub repository.

$ git status
On branch main
Your branch is up-to-date with 'origin/main'.

nothing to commit, working tree clean
$ git remote -v
origin	https://github.com/awdeorio/p4-web.git (fetch)
origin	https://githubcom/awdeorio/p4-web.git (push)

You should have a .gitignore file (instructions).

$ head .gitignore
# This is a sample .gitignore file that's useful for C++ projects.
...

Group registration
Register your partnership (or working alone) on the Autograder. Then, submit the code you have.

Linked list
Implement your doubly linked list in List.hpp. List.hpp.starter provides prototypes for each function. Because List is a templated container, function implementations go in List.hpp. There is no List.cpp.

While the List from lecture was singly linked, this List is doubly linked. This List also contains an iterator interface.

Do not modify the public interface of the List class. Implement a doubly-linked list. No arrays or vectors, etc. Manage memory allocation so that there are no memory leaks (Leak checking tutorial).

Compile and run the provided compile check and List tests.

$ make List_compile_check.exe
$ make List_public_test.exe
$ ./List_public_test.exe

Write tests for List in List_tests.cpp using the Unit Test Framework. You’ll submit these tests to the autograder. See the Unit Test Grading section.

$ make List_tests.exe
$ ./List_tests.exe

Pro-tip: Getting an error about typename? Take a look at our reference on Typename.

Setup
Rename these files (VS Code (macOS), VS Code (Windows), Visual Studio, Xcode, CLI):

List.hpp.starter -> List.hpp
List_tests.cpp.starter -> List_tests.cpp
Edit List.hpp, adding a function stub for each function prototype in List.hpp. Here’s an example.

template<typename T>
bool List<T>::empty() const {
  assert(false);
}

The List tests should compile and run. The public tests will fail until you implement the functions. The file for your test cases (List_tests.cpp) will pass because it initially only contains ASSERT_TRUE(true).

$ make List_public_test.exe
$ ./List_public_test.exe
$ make List_tests.exe
$ ./List_tests.exe

At this point, we haven’t written the List Iterator, so List_compile_check.exe won’t compile. You’ll need to take a look at the lecture about iterators and write your own tests. After you do, use the provided compile check like this:

$ make List_compile_check.exe
Configure your IDE to debug either the public tests or your own tests.

Public tests	Your own tests
VS Code (macOS)	
Set program name to:
${workspaceFolder}/List_public_test.exe

Set program name to:
${workspaceFolder}/List_tests.exe

VS Code (Windows)	
Set program name to:
${workspaceFolder}/List_public_test.exe

Set program name to:
${workspaceFolder}/List_tests.exe

Xcode	
Include compile sources:
List_public_test.cpp, List.hpp

Include compile sources:
List_tests.cpp, List.hpp

Visual Studio	
Exclude files from the build:

Include List_public_test.cpp
Exclude List_compile_check.cpp, List_tests.cpp, api.cpp, main.cpp (if present)
Exclude files from the build:

Include List_tests.cpp
Exclude List_compile_check.cpp, List_public_test.cpp, api.cpp, main.cpp (if present)
