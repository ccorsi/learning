---
layout: resume
title: Maven
subtitle: General Notes
page-width: lg
---

__Table of Contents__

- [Introduction](#introduction)
- [Dependencies](#dependencies)
    - [Adding Dependencies](#add_dependencies)
    - [Create an Executable Jar](#executable_jar)
    - [Add Library Dependencies to the Executable Jar Archive](#add_library_dependencies)
    - [Copy Dependencies to a Directory](#copy-dependencies)

---

# Introduction {#introduction}

This will contain more information about how one can use [Maven](https://maven.apache.org/){:target="_blank"}
to build, test and deploy a java project.  While the prior [Java page](../) contain some information about how
to use Maven.  This page will contain more information on how to use Maven to build, test and deploy Maven
projects.

# Dependencies {#dependencies}

The following sections will describe different ways of adding dependencies and how to include these dependencies
in your packaged archive files used to run your project.

## Adding Dependencies {#add_dependencies}

We shall start this with describing how one goes about adding dependencies to your maven project.  Maven intends
to make the handling of third party packages as simple as possible.  This includes the need to retrieve those
packages and adding them to your build process.  Let us then look at how one goes about adding a dependency to
your maven project.

Let us start by adding the JUnit package to your maven project.  Maven created a repository that includes an assortment
of java packages that one can use called the Maven Central Repository.  This repository can be searched by going
to the [MVN Repository](https://mvnrepository.com/repos/central){:target="_blank"} or to the
[Sonatype Maven Central Repository](https://central.sonatype.com/){:target="_blank"} websites.  Both of these websites
provide search capabilities to allow one to find the required java packages needed for your project.  We can then
search for the JUnit package by entering "junit" in the search input box.  The resulting search will offer you
several java packages that you can choose from but we will then pick the junit-jupiter-engine package.  These
websites make is easy for one to include any of these packages within your maven project by supplying an example
dependency tag.  For instance,

```xml
<dependency>
    <groupId>org.junit.jupiter</groupId>
    <artifactId>junit-jupiter-engine</artifactId>
    <version>5.10.2</version>
</dependency>
```

You can then copy this and include it in your maven project pom.xml file.  This tag needs to be added to the
dependencies tag to be correctly processed by the maven build process.


## Create an Executable Jar {#executable_jar}

We are now going to look how you can use maven to generate an executable jar file.  Recall that an executable
jar file contains a manifest with the Main-Class attroibute set to the fully qualified class name.  Let us assume
that we have a main class named, org.example.Main, that is part of a current maven project.  We are then going
to create an executable jar file.  The first thing that we need to do is include the maven jar plugin.  The
pom.xml file will need to include the following plugin within the build->plugins tag as follows.

```xml
<project>
    ...
    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-jar-plugin</artifactId>
                <version>3.3.0</version>
                <configuration>
                    <archive>
                        <manifest>
                            <mainClass>org.example.Main</mainClass>
                        </manifest>
                    </archive>
                </configuration>
            </plugin>
            ...
        </plugins>
    </build>
    ...
</project>
```

When the _mvn package_ command is executed an executable jar file will be create and located with the target
sub-directory.  The main class can then be executed using the -jar option of the java command as follows.

```sh
$ java -jar <jar-file-name>
```

The above java command will look for the manifest in the passed jar file.  It will then look for the Main-Class
attribute within the jar manifest file.  If it finds, one it will then run the main static method from that
class.  If the main class expects command line arguements then all you need to do is to append the required
command line arguements to the above command.

While the above information is pretty clear there are other configurations that one can set using the
maven-jar-plugin that can be found at the
[Maven Jar Plugin](https://maven.apache.org/plugins/maven-jar-plugin/index.html){:target="_blank"} web page.
In the meantime, we will look at some of the more promising configurations that are useful within maven java
projects.

## Add Library Dependencies to the Executable Jar Archive {#add_library_dependencies}

In my humble opinion, maven strength is its ability to implicitly access and include third party libraries
as part of a maven project.  It simplifies the need to setup the project build and testing process.  The
use of the maven-jar-plugin also simplifies the need to create an executable jar archive that accesses
these third party libraries.  While there are different configurations options that one can use to set the
jar file classpath.  I will assume that we have all the maven project third-party libraries located in the
lib sub-directory where the jar file is located.  Let us look at a simple pom file that contains a third-party
library requirement for a given maven project.

```xml
<project>
  ...
  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-jar-plugin</artifactId>
        ...
        <configuration>
          <archive>
            <manifest>
              <addClasspath>true</addClasspath>
              <mainClass>fully.qualified.MainClass</mainClass>
              <classpathPrefix>lib/</classpathPrefix>
            </manifest>
          </archive>
        </configuration>
        ...
      </plugin>
    </plugins>
  </build>
  ...
  <dependencies>
    <dependency>
      <groupId>commons-lang</groupId>
      <artifactId>commons-lang</artifactId>
      <version>2.1</version>
    </dependency>
    <dependency>
      <groupId>org.codehaus.plexus</groupId>
      <artifactId>plexus-utils</artifactId>
      <version>1.1</version>
    </dependency>
  </dependencies>
  ...
</project>
```

The above pom update will generate the maven project jar file with the manifest Class-Path attribute set to

```
Class-Path: lib/plexus-utils-1.1.jar lib/commons-lang-2.1.jar
```

Thus when the executable jar file is executed where the these jar files are located in the lib sub-directory
where the executable jar file is located.  The main class will be executed and the required dependent
third-party jar archives will be accessible to the java application.

While the above configures that jar archive Class-Path attribute.  It doesn't actually place the required
dependencies with the lib sub-directory.  This will require another plugin to perform that task which will be
described next.

## Copy Dependencies to a Directory {#copy-dependencies}

While the last example updates a jar file manifest file to define the required classpath of the executable
jar file.  It doesn't provide the access to the third-party jar files.  The maven-dependency-plugin is used
to copy the required third-party libraries to a destination directory.  Let us take the prior section lib
sub-directory destination.  Then the project pom file should contain the following plugin definition.

```xml
<project>
  [...]
  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-dependency-plugin</artifactId>
        <version>3.6.1</version>
        <executions>
          <execution>
            <id>copy-dependencies</id>
            <phase>package</phase>
            <goals>
              <goal>copy-dependencies</goal>
            </goals>
            <configuration>
              <outputDirectory>${project.build.directory}/lib</outputDirectory>
              <overWriteReleases>false</overWriteReleases>
              <overWriteSnapshots>false</overWriteSnapshots>
              <overWriteIfNewer>true</overWriteIfNewer>
            </configuration>
          </execution>
        </executions>
      </plugin>
    </plugins>
  </build>
  [...]
  <dependencies>
    <dependency>
      <groupId>commons-lang</groupId>
      <artifactId>commons-lang</artifactId>
      <version>2.1</version>
    </dependency>
    <dependency>
      <groupId>org.codehaus.plexus</groupId>
      <artifactId>plexus-utils</artifactId>
      <version>1.1</version>
    </dependency>
  </dependencies>
  [...]
</project>
```

The jar files plexus-utils-1.1.jar and commons-lang-2.1.jar will be copied to the lib sub-directory within
the target sub-directory.  You can then package these jar files and the executable jar file together and
the executable jar file can be executed with the required third-party library files.

More information about the maven-dependency-plugin can be found at the
[Maven Dependency Plugin](https://maven.apache.org/plugins/maven-dependency-plugin/index.html){:target="_blank"}
website.
