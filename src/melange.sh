#!/bin/bash
cp $1 tempo1

> $2
sed -n "1 p" tempo1 >> $2
sed -e "1 d" tempo1 >> tempo3
mv tempo3 tempo1

nbligne=$(sed -n '$=' tempo1)
nbl=nbligne
min=1

while ((min <= nbligne))
do
    rnd=$((RANDOM%$nbl))
    ((rnd+=1))
    sed -n "$rnd p" tempo1 >> $2
    sed -e "$rnd d" tempo1 >> tempo3
    mv tempo3 tempo1
    ((min+=1))
    ((nbl-=1))
done

rm tempo1
