AQuery to Q (A2Q)
----------------

A2Q is a project that morphed out of my independent research course for Spring 2015, carried
out under the supervision of Dr. Dennis Shasha.

It compiles [AQuery](http://dl.acm.org/citation.cfm?id=1315482) into [q](https://kx.com/),
providing users with two advantages:

* Allows users to query kdb databases with a syntax similar to SQL
* Heuristic, order-based optimizations, which provide performance advantages, while maintaining
readability
* Compilation into transparent q code (allowing experienced users to inspect the code executed)

The transformations on queries provide the same semantics at a fraction of the cost. These involve:
pushing selections below sorting, removing unnecessary sorts, maintaining order across local tables,
and others.

In order to build, simply

```
cd src; make;
```

Given that the code generated targets kdb, users seeking to actually run any code
generated should also install q.

A2Q is meant for *nix. There are no plans on making this available for windows.
