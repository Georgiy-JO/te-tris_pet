#!/bin/bash
#don't forget to commit (unless u use option 9)
#origin -- gitlab for s21
#hub -- github
#branch list: master develop 
var_active_branch="develop"
var_base_branch="develop"

if [ $1 -eq 1 ]; then
  git push origin $var_active_branch
  echo "
◑ ◔
╔═╗
║▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
╚═╝"
  git push hub $var_active_branch
elif [ $1 -eq 0 ]; then
  git push origin $var_base_branch
  echo "
◑ ◔
╔═╗
║▓▒░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░
╚═╝"
  git push hub $var_base_branch
else
  echo "wrong command..."
fi
  
