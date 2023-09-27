#! /usr/bin/env python

import sys, os, fnmatch

# print('This message will be displayed on the screen.')


def find(pattern, path):
    original_stdout = sys.stdout # Save a reference to the original standard output
    with open('Proton_embedding_new.list', 'a') as f:
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

#proton
find('*.MuDst.root', '/star/data105/embedding/production_isobar_2018/ProtonNew_100_20201503');
find('*.MuDst.root', '/star/data105/embedding/production_isobar_2018/ProtonNew_101_20201503');

#AntiProton
