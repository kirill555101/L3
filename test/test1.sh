#!/bin/bash

rm hw.data
./main.out < test/1.test > test/1.result
diff test/1.sample test/1.result
