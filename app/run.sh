cd ..
mkdir build
cd build
cmake ..
make
./app/pdecracker
python3.11 ../app/plot.py
