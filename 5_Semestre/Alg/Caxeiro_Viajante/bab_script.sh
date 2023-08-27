for i in 16 17 18 19 20 25 26 27 28 29 36 37 38 39 40 49 50 51 52 53 64 65 66 67 68 81 82 83 84 85
do
    echo "seed: ${i}" 
    python3 $1 -a BaB -d "euclidian" -e 4 -s $i >> "output_BaB_euclidian".txt &
    python3 $1 -a BaB -d "manhattan" -e 4 -s $i >> "output_BaB_manhattan".txt &
    wait
done