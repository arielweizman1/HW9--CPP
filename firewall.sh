#!/bin/bash
##
# @brief print the uniq packets that passed the rules.
# @param $1 -the rules
# @param argv An explanation on the "argv" parameter
##

rules=$(cat $1 | sed 's/#.*//' | sed '/^[[:space:]]*$/d' | sed 's/ //g')
while read packet; do
  for rule in $rules; do
    rule1=$(echo $rule | cut -d"," -f1)
    result1=$(echo $packet | ./firewall.exe "$rule1")
    if [[ "$result1" == "" ]]; then
      continue
    fi
    rule2=$(echo $rule | cut -d"," -f2)
    result2=$(echo $packet | ./firewall.exe "$rule2")
    if [[ "$result2" == "" ]]; then
      continue
    fi
    rule3=$(echo $rule | cut -d"," -f3)
    result3=$(echo $packet | ./firewall.exe "$rule3")
    if [[ "$result3" == "" ]]; then
      continue
    fi
    rule4=$(echo $rule | cut -d"," -f4)
    result4=$(echo $packet | ./firewall.exe "$rule4")
    if [[ "$result4" == "" ]]; then
      continue
    fi
    echo "$packet"
  done
done | sort -u | sed 's/ //g'
