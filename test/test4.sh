#!/bin/bash

./main.out < test/4.test > test/4.result
diff test/4.sample test/4.result
