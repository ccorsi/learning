---
layout: resume
title: Development Building Tools 
subtitle: What I know
cover-img: "/assets/img/gratisography-224H-free-stock-photo.jpg"
---

# Introduction

Here I will discuss the different development building tools that I have used in and out of a working environment.  These tools have been mainly used to build
products using C/C++ and Java.  There are also some tools that I have used to build products using Python that I haven't used within a working environent. In
what follows, I will be discussing how each of these tools were used in and out of a working environment.

# Make and CMake

The use of make and its other flavors like nmake and cmake is something that I have used throughout my career.  These tools have become an essential part of the
building and testing of products that I have been involved with.  The earlier years of my career required that I understand how to create and update Makefiles.
This was required because at that time, we didn't have interactive development tools that could generate the require Makefile targets for you.  The need to be
able to understand and extend the definitions of Makefiles allowed me to be able to gain knowledge of how to build products using these tools.  This has helped
me better understand the options that different compilers use to build products.

While the need to be able to understand how to define Makefiles during the earlier years of my careet.  This need became less of a need throughout my later
years developing products using C/C++.  The IDE reduce the need to be able to understand how to define and use a Makefile.  This allow me to spend more time
working on developing the product and less time updating the build process.  Granted this has allowed me to focus more on what needs to be done and less on
supporting the build process.  Nonetheless, the advent of Visual Studio and other IDE has provided some releaf in this respect.

# Maven

I have used the [Maven](https://maven.apache.org) build process in and outside of a working environment.  This has been used to build, test and package 
products.  I have had to understand how the different plugins are confgured and used.  As part of that work, I have also had a chance to use this tool
to create personal projects that I have not been part of my working environment.  This in turn has provided me with the ability to expand my knowledge
of the different plugins that were not used within a working environment.

# Ant/Ivy

This build tool was used by one of the products that I worked with to build different modules of our product.  It was used to run our build process for our
C/C++ source code, our Java source code and finally our .NET source code.  At the time, that our product was being developed this build system provided the
greatest flexibility for to be able to build our product with.  As our product evolved, we started to incorporate the [Ivy](https://ant.apache.org/ivy/) build
system.  This was done to remove the need to commit libraries into our repository and instead store them within a central repository.  In our case, we used
[Archiva](https://archiva.apache.org/) to store these libraries and that required that we integrate Ivy within our build process to be able to download those
libraries from the Archiva server.

# Conclusion

While I have mentioned many build tools here.  They are not the only ones that I have worked with.  There are others that I have had a chance to work with
outside of a work environment.   For instance, I have worked somewhat with the gradle build tool but not enough to be comfortable with since I have not had
a need to understand that tool.  This is just an example of what I have touch on but not necessarily mastered.

{% comment %}

Here are a list of the building tools that I have used within a work environment:

	- nmake (Object Design/Progress Software/CIBER/Veritech)
	- make (Object Design/Progress Software/Riverbed/Aternity/Bell Sygma/Ranmar Business System)
	- maven (Object Design/Progress Software/Riverbed/Aternity/FUSESource)
	- cmake (Riverbed/Aternity)
	- Ant/Ivy (Object Design/Progress Software/Riverbed/Aternity)

Here is a list of build tools that I'd like to be able to learn:

	- gradle

What other tools have I used to build the product?  I can talk about my use of Nexus and Archiva.
Specifically, how I have used Nexus as a local distribution of the different libraries used within
my projects such that they aren't accessed within our company intranet everytime I build my product
locally on my machine.  Explain how this was setup on a guest vm and used by one or more vm to get
the required libraries during my build process.

{% endcomment %}

{% comment %}
turn-on-auto-fill

Local Variables:
backup-inhibited: t
fill-column: 160
End:

{% endcomment %}
