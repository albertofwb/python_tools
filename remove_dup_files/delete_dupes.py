#!/usr/bin/python
import os

class Delete(object):
    '''Delete Methods For File Objects'''

    def __init__(self, file):
        self.file = file

    def interactive(self):
        '''interactive deletion mode'''
        choice = raw_input('Do you really want to delete %s [N]/Y' %self.file)
        if choice.upper():
            print 'DELETING: %s' %self.file
            status = os.remove(self.file)
        else:
            print 'Skipping: %s' %self.file
        return

    def dryrun(self):
        '''simulation mode for deletion'''
        print 'Dry Run: %s [NOT DELETED]' %self.file
        return

    def delete(self):
        '''Performs to delete on a file, with additional conditions'''
        print 'DELETING: %s' %self.file
        try:
            status = os.remove(self.file)
        except Exception, err:
            print err
            return status

if __name__ == '__main__':
    from find_dupes import find_dupes
    dupes = find_dupes('/tmp')

    for dupe in dupes:
        delete = Delete(dupe)
        delete.delete()

