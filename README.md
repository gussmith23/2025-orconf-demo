# Yosys + egglog: Supercharge your passes with Equality Saturation

**Background:** at this year's Latch-Up in Santa Barbara, I spoke with a group of people about equality saturation (eqsat) during the un-conference.

This made me realize I could make an easy on-ramp to using eqsat with hardware via a Yosys pass.

This demo presents a (very rough) version of that pass!

**Goal:** give people an easy way to play with equality saturation for hardware via Yosys. If you already have a Yosys flow, this should* just work!

(*it will definitely break, but I will fix it)

## What is Equality Saturation? What is egglog?

Equality saturation is a program optimization/transformation technique that's becoming increasingly popular in hardware design/EDA workflows. See some example papers:

* [Equality Saturation for Circuit Synthesis and Verification (Sam Coward's thesis)](https://samuelcoward.co.uk/assets/pdf/Thesis_Imperial.pdf)
* [ESFO: Equality Saturation for FIRRTL Optimization](https://dl.acm.org/doi/abs/10.1145/3583781.3590239)
* [Scaling Program Synthesis Based Technology Mapping with Equality Saturation](https://arxiv.org/abs/2411.11036)
* [Equality Saturation for Datapath Synthesis: A Pathway to Pareto Optimality](https://ieeexplore.ieee.org/abstract/document/10247948)

Anecdotally, I have heard of major EDA vendors also beginning to use eqsat in their tools.

At the core of eqsat is the **egraph** datastructure: essentially, an efficient database for storing programs.

The egraph on the left transforms into the egraph on the right when we transform the multiplication by two into a left shift by one:

![egraph](assets/egraph.png)

As you can see, 





[](https://egraphs-good.github.io/egglog-demo/?example=eqsat-basic)


[simple hw demo](https://egraphs-good.github.io/egglog-demo/?program=XQAAgAB7AgAAAAAAAAAUHMnnVi1HmurH0_ncX6dnJVwUBmLVa-mxsg6huddnznArUb1o0sC53b1M8A15UyGzSL6rtLOzjsOXlR8ADcHr5Q-S8wHy0EObEiZb6pJCGOJFh67tDMaN9yp08P4F1mZ2_IXIZGdj6AHtzQ-nLJkgkIhKnsOgVoFzS-C0EYNivO8QJWzf0IRagVe7Pjzxddsq7obfIGEiI9bbxy-YvD2TyYXzKBfrF1gwgn89dUjIO0kdIt5qjtdD9aRmtHK17SpyH7QOQd2SzPGFLorR2S0zbcZOf3n1bW9K-Dv-lXXQ9XabukoOO-od8keNaabzMtP2H3mGhQ3FxwEPBSwmJ9BX_MGIxKQ-Hu5a3FjntOZIzmyArO310zRKZhgWHHmkdueteLZxzKEKswZLPzFCva_X_53DGwA%253D)

```
git clone --recursive https://github.com/gussmith23/2025-orconf-demo
cd 2025-orconf-demo
make -C yosys-plugin
make -C churchroad/yosys-plugin
./examples/simple/run.sh
```