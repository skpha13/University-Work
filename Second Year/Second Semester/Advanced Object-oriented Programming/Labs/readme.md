# Tools and setup

#### JDK
- Download Windows/x64	 zip from https://jdk.java.net/21/
   Extract zip file into a folder (eg: C:\Program Files\Java\jdk-21)

   OR
- Download x64 Installer from https://www.oracle.com/java/technologies/downloads/#jdk21-windows and run it

- Add the location of the bin folder of the JDK installation to the PATH variable in System Variables
- Set JAVA_HOME: Under System Variables, click New -> Enter the variable name as JAVA_HOME -> Enter the variable value as the installation path ofthe JDK (eg. C:\Program Files\Java\jdk-15.0.2)
- To test installation -> Open the Command Prompt and type java -version

#### IDE
You will need an IDE that supports Java.
Some examples:
- IntelliJ IDEA - needs a licence, but they offer free ones for students (https://www.jetbrains.com/community/education/#students)
- Eclipse EE - https://www.eclipse.org/downloads/packages/installer

#### GitHub
Create a Github account: https://github.com/
Git
Install git from: https://git-scm.com/download/win

#### Apache Maven 
(if needed in your project)
- Download latest bin.zip from: https://maven.apache.org/download.cgi
- Add the location of bin folder of Maven installation to the PATH variable in System Variables
- To test installation -> Open the Command Prompt and type mvn -v