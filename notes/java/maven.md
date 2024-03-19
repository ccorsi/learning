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
jar file contains a manifest with the Main-Class attroibute set to the fully qualified class name.

