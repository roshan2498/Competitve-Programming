# Stress testing
In competitive programming, stress testing is a technique of testing your solution on a multitude of random test cases to find possible bugs and problems in the code.

Often, stress testing is performed with the help of a "stupid" brute-force solution for the problem, that may work correctly only on small test cases. The output of your solution is then compared against the output of the stupid solution to find possible mismatches.

### Example problem

Let's consider the following simple problem. You are given an integer number \(n\) greater than \(1\), and you need to tell if it is a prime number or not. If it is, you print "YES", otherwise you print "NO".

You write the following optimal solution, that works in \(O(\sqrt{n})\) time by checking all the possible divisors up to the square root of \(n\). Unfortunately, there is some bug, and you get a "WRONG ANSWER" verdict.

```
#include <iostream>
#include <cstdio>

using namespace std;

int n;

bool isPrime(int n) {
  for (int i = 2; i * i < n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);

  if (isPrime(n)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
```

<br>
Optimal solution checking the divisors up to the square root of \(n\). Can you spot the bug?

Usually, to catch the bug you run your solution on more test cases, talk to the teammate, rewrite some part of the code, or simply stare at the screen hoping to find the problem. But what if nothing works?

In a problem like this, it may be tricky to write an optimal solution, but it's very simple to write <i>some</i> solution: let's just check all the possible divisors of \(n\):

```
#include <iostream>
#include <cstdio>

using namespace std;

int n;

bool isPrime(int n) {
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

int main() {
  scanf("%d", &n);

  if (isPrime(n)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

  return 0;
}
```

<br>
Slow but correct solution checking all the possible divisors of \(n\).

Now we have our optimal, but buggy, solution, and a slow solution that definitely works. We can run both solutions on a bunch of tests, and see where they produce different results. The essence of stress testing is to automate this process.

## Components of stress testing

There are several components of stress testing. Let's cover them one by one.

<b>1. Model solution</b>. The solution that you want to stress test. In our example, it's an optimal \(O(\sqrt{n})\) solution. You may already know that the model solution is buggy, or you may stress test it in advance to catch any possible bugs.

<b>2. Stupid solution</b>. Usually, a brute-force solution that solves the given problem. It should be easy to write, and simple enough so that you can be sure it is correct. It may be too slow, or work only on the small test cases – therefore "stupid".

<b>3. Test case generator.</b> Now that you have a model solution and a stupid solution, you can already compare their results manually. But to make this process much more efficient, let's automate it.

For this, let's write another program that will generate a random test case. Keep problem constraints in mind, and keep the tests small so that the stupid solution works on them. You also don't want the tests to be too big anyway, as it would be hard to make sense of them later.

For our example problem, let's write a generator that produces a test case with a number between \(2\) and \(1000\):

```
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  // Use first command line argument as a seed.
  srand(atoi(argv[1]));

  int n = rand() % 999 + 2;
  printf("%d\n", n);

  return 0;
}
```

<b>4. Stress testing script.</b> Now, to do the actual stress testing, let's write a script that will in a loop generate a new test case, and compare the output of both solutions. The loop will finish once the two solutions produce different results.

Here is a shell script like this written in bash for Linux and Mac systems:

```
#!/bin/bash

# solution.cpp  solution you want to stress test
# stupid.cpp    stupid solution for the problem
# gen.cpp       generates a new random test case for the problem

# compile all programs first
g++ solution.cpp -o solution
g++ stupid.cpp -o stupid
g++ gen.cpp -o gen

for ((i = 1; ;i++)) do
  # generate a new test case in the file named "in"
  # note that we pass i as a random seed to the generator
  ./gen $i > in
  # redirect the solution output to the "out" file
  ./solution < in > out
  # redirect the stupid solution output to the "out-stupid" file
  ./stupid < in > out-stupid

  # compare both outputs.
  # if outputs are different, echo the
  # corresponding message and break the loop.
  # failing test will be in the "in" file.
  if ! cmp -s out out-stupid
  then
    echo 'Found failing test!'
    break
  fi

  # if outputs are the same, we echo "OK".
  # this is optional, but helps to see the progress of stress testing.
  echo 'OK'
done
```

To run the script, execute the following commands in your terminal:

```
# assume script is named stress.sh
sh stress.sh

# alternatively:
# chmod +x stress.sh
# ./stress.sh
```

For our example, the script will print "OK" for a while, meaning both solutions produce the same result, and then output "Found failing test!" and stop once the results are different. The test where outputs are different will be in the \(in\) file.

Because of the random generation of the tests, the script will take a different amount of time each run. I recommend running it multiple times yourself to see how it works for you.

And here is a similar batch script for Windows:

```
@echo off

g++ solution.cpp -o solution.exe
g++ stupid.cpp -o stupid.exe
g++ gen.cpp -o gen.exe

set i=0

:loop
  gen.exe %i% > in
  solution.exe < in > out
  stupid.exe < in > out-stupid

  fc out out-stupid
  if errorlevel 1 goto fail

  echo OK
  set /a i=%i%+1
  goto loop

:fail
  echo Found failing test!
```

Assuming the script is in the file \(stress.bat\), you can simply call it with the following:

```
stress.bat
```

## Variations

The stress testing we introduced so far was using the model and stupid solutions, but there are several possible variations:

*     Instead of a stupid solution that you write yourself, you may already have a different correct solution for the problem, written by you or by somebody else. In this case, you may test your model solution against it.
*     Sometimes there are several possible correct answers to the problem you solve. In this case, it's not enough to just compare the output of your model solution with the output of some other solution. To handle this, you need another program called <b>checker</b>, that will check the output for correctness.<br>
<br>
    For example, if the problem you solve is to output a prime factorization of an integer \(n\)<i>in any order</i>, for \(n = 35\) the output can be both \(5 \times 7 \) and \(7 \times 5 \). The checker needs to check that each output number is prime and that the product of all numbers is indeed \(n\).<br>
<br>
    If you write a checker, you usually don't need a stupid solution at all. On the downside, sometimes writing a checker can be as hard or even harder than solving the actual problem.
*     Another option is instead of having multiple solution and script files, to do the stress testing in a single solution file. For our example problem, you could have two functions \(isPrime(int\:n)\) and \(isPrimeStupid(int\:n)\), doing optimal and brute-force checks respectively, and a function \(gen()\) generating a random number. Then in the main function, you could run a loop comparing the outputs of both functions, similar to the stress testing script.<br>
<br>
    For some problems, this approach can simplify the stress testing workflow. On the downside, you will have to make sure that all the variables and data structures are well separated between optimal and stupid solutions in a single source code file.

There are many other variations possible. What's important to remember here is that stress testing is not a particular set technique, but rather a useful approach to somehow automatically test your solution until you find a problem.

## When to write stress tests

Finally, there is a strategic question of <i>when</i> it makes sense to write stress tests. Here is some advice on this.

First, it is worth writing stress tests only when it's easy and fast to write a stupid solution and test generator. It should take up to 5-10 minutes max.

In competitions where you can submit multiple times and there are many problems (ICPC, Codeforces, Topcoder, and similar), it generally makes sense to write stress tests when it's easy or you don't have anything better to do. Of course, this depends on the particular rules of the competition you are in. It also may make sense to write stress tests in advance, before you even submit, if a lot depends on the next submission.

In the old-IOI style competitions, when you can submit only once or don't know the results until the end of the contest, it makes sense to always write stress tests when you have time. In competitions like these, it's extra important to make sure your solution doesn't have any stupid bugs, and stress testing is a great way to do this.

