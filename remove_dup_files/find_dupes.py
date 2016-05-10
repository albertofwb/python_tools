from checksum import create_checksum
from diskwalk_api import diskwalk
from os.path import getsize

def find_dupes(path = '/tmp'):
    dup = []
    record = {}
    files = diskwalk(path).enumerate_paths()
    for file in files:
        try:
            compound_key = (getsize(file), create_checksum(file))
            if compound_key in record:
                dup.append(file)
            else:
                #print 'Creating compound_key record:', compound_key
                record[compound_key] = file
        except:
            pass
    return dup

if __name__ == '__main__':
    dupes = find_dupes()
    for dup in dupes:
        print 'Duplicate: %s' %dup
