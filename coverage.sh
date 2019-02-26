#!/usr/bin/env bash

EXCLUDED="'/usr/*' '${HOME}/.cache/*' './deps/*'"

lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info ${EXCLUDED} --output-file coverage.info
lcov --list coverage.info
bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"