#!/bin/bash

bin/hw < test/3.test > test/3.result
diff test/3.sample test/3.result
