#!/bin/bash
cp $1 tempo1
nbligne=$(sed -n '$=' tempo1)
nbl=nbligne
min=2
> $2
while ((min <= nbligne))
do
    rnd=$((RANDOM%$nbl+1))
    ((rnd+=1))
    sed -n -e "$rnd p" tempo1 >> $2
    sed -e "$rnd d" tempo1 >> tempo3
    mv tempo3 tempo1
    ((min+=1))
    ((nbl-=1))
done

rm tempo1
