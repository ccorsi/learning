# Introduction

The following sub-project contains implementations of different algorithms that I learned when auditing a university course
at Columbia University.  It is with sadness to note that this course was discontinued since I really enjoyed the professor
teaching this class.  In my humble opinion, she created a very good course that offered an overview of the field of AI.  I
only wished that Columbia University would reconsider reviving this class and the other classes that were part of the
MicroMasters Program.

That said, this particular project contains the different search implmentations that were taught during one of those classes.
Specifically, it will contain implementations for the different uninformed and informed algorithms.  These implementations
will be implemented using C++ templates so that they can be used with any type of elements.  It is hoped that these
implementations might be of use by others.

# Implementations

We are now in a position to expand on the different type of Search algorithms that will be implemented in the following
section.  This will include information about the different algorithms that will be implemented.  With that, we can end
up including more details about each of these algorithms so that the user of these algorithms can make an informed
decision about which one to use.

Here is a detailed list of the different algorithms that have been or will be implemented here.

| Algorthm | Description |
| -------- | --------- |
| Breath First Search | TBD |
| Depth First Search | TBD |
| Depth Limited Search | TBD |
| Iterative Deepening Search | TBD |
| Uniform Cost Search | TBD |
| Greedy Best First Search | TBD |
| A* Search | TBD |
| IDA* Search | TBD |

While the following list shows which of the above algorithms have been implemented

- [x] Breath First Search
- [x] Depth First Search
- [x] Depth Limited Search
- [x] Iterative Deepening Search
- [x] Uniform Cost Search
- [] Greedy Best First Search
- [] A* Search
- [] IDA* Search

The above algorithms are part of a class of algorithms called **Goal-based Agents** that are used as
problem solving agents or planning agents.

## Goal-based Agents

Goal-based agents have the following conditions

- Agents that work towards a **<span style="color:magenta">goal</span>**
- Agent consider the impact of **<span style="color:magenta">actions</span>** on future
    **<span style="color:magenta">states</span>**
- Agent's job is to identify the action or series of actions that lead to a goal
- Formalized as a **<span style="color:magenta">search</span>** through possible
    **<span style="color:magenta">solutions</span>**

Given the above conditions that an agent is supposed to be able to follow.  We should then define
the formulation of the problem as follows:

- **<span style="color:blue">Initial state:</span>** the state in which the agent starts
- **<span style="color:blue">States:</span>** All states reachable from the initial state by
    any sequence of actions (**State space**)
- **<span style="color:blue">Actions:</span>** possible actions available to the agent.  At a
    state <ins>s</ins>, <ins>Actions(s)</ins> returns the set of actions that can be executed in
    state <ins>s</ins>. (**Action space**)
- **<span style="color:blue">Transition model:</span>** A description of what each action does
    <ins>Results(s,a)</ins>
- **<span style="color:blue">Goal test:</span>** determines if a given state is a goal state
- **<span style="color:blue">Path cost:</span>** function that assigns a numeric cost to a path
    with respect to performance measure

The above definitions will relagate any of the different search algorithms will define the search region
as:

- The search space is divided into three regions:
  1. **Explored**
  2. **Frontier**
  3. **Unexplored**


## Some General Information

Before we talk about the implementations of the different algorithms.  We will discuss some general assumptions
about this algorithms.  Specifically, what each of the different references in the algorithm implementation is
describing.  Each of these algorithm will contain at least one of the following information.

## Breath First Search

The breath first search algorithm will

## Depth First Search

## Depth Limited Search

## Iterative Deepening Search

## Uniform Cost Search

## Greedy Best First Search

## A* Search

## IDA* Search
