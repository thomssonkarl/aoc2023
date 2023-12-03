#!/bin/bash

if [ "$#" -ne 2  ]; then
  echo "Usage: $0 <session_token> <day_number>"
    exit 1
    fi

    SESSION_TOKEN=$1
    DAY_NUMBER=$2

    URL="https://adventofcode.com/2023/day/$DAY_NUMBER/input"

    wget "$URL" --header "Cookie: session=$SESSION_TOKEN" -O "input$DAY_NUMBER.txt"

    echo "Input for day $DAY_NUMBER downloaded successfully."

