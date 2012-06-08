#!/bin/sh

size=256
for ((  i = 37 ;  i <= 50;  i++  ))
do
   #echo "$i"
   offset=$( echo "$i * 0.2" | bc )
   #echo "offset: $offset"
   #echo "images/pokeball$i.tga"
   echo "./dangerclose -w $size -h $size -f 1.1f -p 0.6f -i input/pokeball.pov -o $offset"
   ./dangerclose -w $size -h $size -f 1.1f -p 0.6f -i input/pokeball.pov -o $offset
   if [ $i -lt 10 ]; then
      echo "mv images/pokeball.tga images/pokeball_big/pokeball0$i.tga"
      mv images/pokeball.tga images/pokeball_big/pokeball0$i.tga
   else
      echo "mv images/pokeball.tga images/pokeball_big/pokeball$i.tga"
      mv images/pokeball.tga images/pokeball_big/pokeball$i.tga
   fi
done
