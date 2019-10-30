# Job Shop Solver

# Index
- Introduction
- How to run the code?
- references

# Introduction

The job shop chedule is a problem well know by the reserchrs. This repository have the implementation of the branch and bound algorithm. That's an exact algorithm that solve the job shop problem where the jobs and machines number is the same. Our implementation is highly inspired in the implementation of the branch and bound algorithm to solve job shop in the webpage **geeks of geeks**. If you pefer the code without OO them just look at the reference and access the **geeks for geeks** implementation with C, it's the same algorithm, but our have OO.
This implementation was made to have a better undestanding of the branch and bound algorithm, there's a lot better algoritms than that.

# How to run the code?

To run this code is nescessary to have make instaled, if you don't have just run the command below:

```bash
$ apt install make
```
After install the make you need to run the command **make**

```bash
$ make
```

this compile, run, write the results to files and clean the executables. The results are into **branchAndBound4x4.txt** and **branchAndBound10x10.txt**.

# References

- Branch and bound implementation to solve job shop: https://www.geeksforgeeks.org/job-assignment-problem-using-branch-and-bound/