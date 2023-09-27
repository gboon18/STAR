#! /usr/bin/env python

import sys, os, fnmatch

# print('This message will be displayed on the screen.')


def find(pattern, path):
    original_stdout = sys.stdout # Save a reference to the original standard output
    # with open('Piplus_embedding.list', 'a') as f:
    # with open('Piminus_embedding.list', 'a') as f:
    # with open('Kplus_embedding.list', 'a') as f:
    with open('Kminus_embedding.list', 'a') as f:
    # with open('Proton_embedding.list', 'a') as f:
    # with open('AntiProton_embedding.list', 'a') as f:
        result = []
        for root, dirs, files in os.walk(path):
            for name in files:
                if fnmatch.fnmatch(name, pattern):
                    result.append(os.path.join(root, name))
                    sys.stdout = f # Change the standard output to the file we created.
                    print(os.path.join(root, name))
                    # print('\n')
                    sys.stdout = original_stdout # Reset the standard output to its original value
    # print result
    return result

# Piplus
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_100_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_200_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_201_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_202_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_203_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_204_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_205_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_206_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_207_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_300_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_500_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piplus_501_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/PiplusHighPt_100_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/PiplusHighPt_200_20201503');

# Piminus
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_200_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_201_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_202_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_203_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_204_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_205_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_206_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Piminus_207_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/PiminusHighPt_200_20201503');

# #Kplus
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Kplus_200_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Kplus_201_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/KplusHighPt_200_20201503');

# #Kminus
find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Kminus_200_20201503');
find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Kminus_201_20201503');
find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/KminusHighPt_200_20201503');

#proton
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_200_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_201_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_300_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_301_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_302_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_303_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_304_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/Proton_600_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/ProtonHighPt_200_20201503');

#AntiProton
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/AntiProton_200_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/AntiProton_201_20201503');
# find('*.MuDst.root', '/star/embed/embedding/production_isobar_2018/AntiProtonHighPt_200_20201503');
