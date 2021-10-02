#!/bin/bash

bin/hw < test/2.test > test/2.result
diff test/2.sample test/2.result
