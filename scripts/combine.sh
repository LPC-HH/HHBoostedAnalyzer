for i in 2022 2023 2024; do for j in ${i}/*; do  echo "hadd combined/${j}.root ${j}/*.root " ; done; done > h.sh
