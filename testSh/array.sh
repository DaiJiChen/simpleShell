#!/bin/bash

declare -a site=(["google"]="www.google.com" ["baidu"]="www.baidu.com")

echo "数组的键为: ${!site[*]}"
