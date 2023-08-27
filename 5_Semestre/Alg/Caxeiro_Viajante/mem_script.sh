for ((exp=4; exp <=10; exp++))
do
    
    python3 $1 -a TAT -d euclidian -e $exp -s 100 >> mem/"TAT_euclidian_${exp}".txt &
    python3 $1 -a Chris -d euclidian -e $exp -s 100 >> mem/"Chris_euclidian_${exp}".txt &
    python3 $1 -a TAT -d manhattan -e $exp -s 100 >> mem/"TAT_manhattan_${exp}".txt &
    python3 $1 -a Chris -d manhattan -e $exp -s 100 >> mem/"Chris_manhattan_${exp}".txt &
    wait

done
