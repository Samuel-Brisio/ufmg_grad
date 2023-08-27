for algorithm in TAT Chris
do
    for dist in euclidian manhattan
    do
        for exp in 4, 5, 6, 7, 8, 9, 10
        do
            for (( i=4;i<10;i++ ))
            do
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+0)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+1)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+2)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+3)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+4)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                python3 $1 -a $algorithm -d $dist -e $exp -s $(($i*$i+5)) >> mem/"output_${algorithm}_${dist}_${exp}".txt &
                wait
                
            done

        done
    done
done