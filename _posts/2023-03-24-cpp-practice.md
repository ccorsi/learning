---
layout: post
title: Getting Reacquainted with C++
subtitle: The road back to competence
tags: [C++, CMake, GoogleTest, Visual Studio Code]
cover-img: /assets/img/path.jpg
# thumbnail-img: /assets/img/thumb.png
# share-img: /assets/img/path.jpg
---

Having spent the better part of my career moving from one programming language to another.  It has become apparent
that moving from one programming languange to another is not always that simple.  It always does
require some time to wrap my mind around working in another programming language.  This doesn't imply that
developing in that programming language is difficult.  It just means that the move from one to the other requires
some adjustment.  This is similar to how one moves from one spoken language to another.  It isn't always easy to
transfer from one language to another.  You need to start to think in the other language.  We tend to initially
think in our predominate language, convert what we want to say into the new language and then voice it.  This
process is time consuming.  So we strive to think in the language we want to speak so that the process of
conversing is much more fluid.   This also goes with moving from one programming language to another.  This is thus
the case with me getting back to using C/C++.

I have been mainly working with Java based programming languages recently.  The ones I have been working with have
been Java, Groovy and JavaScript.  While each of these have their subtleties.  They are nonetheless fairly similar.
During this time, I have also used Python, C# and C/C++.  My use of the C/C++ programming language has been
the one that I have used to least.  This doesn't imply that I had a minimal understanding of the language.  It
just means that my knowledge of it requires some effort to bring it to the forefront.  While this being the case.
I have decided to work on bring that knowledge more easily to the forefront.  Thus, I have started
to solve the different problems that are part of the
<a href="https://www.techiedelight.com/" target="_blank">Techie Delight &lt;/&gt;</a> website.  I could of solved
then using any of the other programming languages but I decided to only solve these problems using C/C++.

When I initially started solving these problems.  I realized that I needed to create a build environment.  I
then decided to use <a href="https://cmake.org/" target="_blank">CMake</a> as a building tool.  The use of this
build tool was mainly to be able to feel comfortable using it since it is something that is being used more 
frequently by different companies.  With my decision to use CMake came the need to decide which IDE to use
with CMake.  While looking around it because quite clear that
<a href="https://code.visualstudio.com/" target="_blank">Visual Studio Code</a> was the best option.  It provided
the ability to build, run, debug and test C/C++ applications on mutiple platforms.  While also providing a CMake
extension.  With this being decided, I finally started to code my solutions in C/C++.

The beauty of solving problems from websites like Techie Delight &lt;/&gt;, is the consistency between each
problem.  One just needs to be able to use a template that can then be replicated between problems.  What I mean
here is not only how to read the problems but also how to setup those problems.  This processed started by
realizing that I needed to use the tests that are part of the different problems.  Since, these tests are a
starting point to finding a solution.  A testing framework was required.  I then looked at
<a href="http://google.github.io/googletest/" target="_blank">GoogleTest</a> and decided to start to use that
framework to run the tests for each of the different problem solutions.  The reason that I decided to use GoogleTest
is similar to the reason that I decided to use CMake.  These tools are being used more throughout the
industry and getting better acquainted with them makes sense.

Now that I had decided what to use to build and run the solutions with.  It was now time to tackle the different 
problems on Techie Delight &lt;/&gt;.   This was how I started getting back into developing using the C/C++
programming language.  While this post only describes the initial work I need to get myself back into C/C++.
This is not the end of this journey and I will continue to talk more about me using C/C++ relative to
solving those problems.  In the meantime, you can checkout my progress on my
<a href="https://github.com/ccorsi/learning/tree/cpp_data_structs_and_algos" target="_blank">cpp_data_structs_and_algos</a>
GitHub branch.
