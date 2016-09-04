#!/bin/bash/
cd ../bin
for i in `seq 1 200`;
do
	./Connect4_3X3O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat

	./Connect4_3X4O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat

	./Connect4_3X5O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat

	./Connect4_3X6O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
done
echo "Batch 0: done"
for i in `seq 1 200`;
do
	./Connect4_3X3O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat

	./Connect4_3X4O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat

	./Connect4_3X5O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat

	./Connect4_3X6O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
done
echo "Batch 1: done"
for i in `seq 1 200`;
do
	./Connect4_3X3O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat

	./Connect4_3X4O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat

	./Connect4_3X5O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat

	./Connect4_3X6O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
done
echo "Batch 2: done"
for i in `seq 1 200`;
do
	./Connect4_3X3O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat

	./Connect4_3X4O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat

	./Connect4_3X5O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat

	./Connect4_3X6O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
done
echo "Batch 3: done"
for i in `seq 1 200`;
do
	./Connect4_3X3O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X3O.dat
	./Connect4_3X3O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat
	./Connect4_3X3O.exe rp rp -v -3 -of ../analytics/rp-3X3O.dat

	./Connect4_3X4O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X4O.dat
	./Connect4_3X4O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat
	./Connect4_3X4O.exe rp rp -v -3 -of ../analytics/rp-3X4O.dat

	./Connect4_3X5O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X5O.dat
	./Connect4_3X5O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat
	./Connect4_3X5O.exe rp rp -v -3 -of ../analytics/rp-3X5O.dat

	./Connect4_3X6O.exe ai -ab -d 4 ai -ab -d 4 -v -3 -of ../analytics/ab-4-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 5 ai -ab -d 5 -v -3 -of ../analytics/ab-5-3X6O.dat
	./Connect4_3X6O.exe ai -ab -d 6 ai -ab -d 6 -v -3 -of ../analytics/ab-6-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
	./Connect4_3X6O.exe rp rp -v -3 -of ../analytics/rp-3X6O.dat
done
echo "Batch 4: done"