for i in {1..1000}
   do 
      ./dist/Release/GNU-MacOSX/ibmflu -f 2  &
      my_pid=$!
      wait $my_pid
      if [ $? -ne 0 ]
         then exit $?
      fi
   done