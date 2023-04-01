#ifndef table_h
#define table_h
#include "storable.cpp"
#include "error.cpp"
#include<vector>
#include<string>
#include<fstream>
using namespace std;
template <class T> class Table{
    private:
        string fileName;
        fstream fileStream;
        vector<Storable *> * records = NULL;
        T * getReferenceOfRecordForId ( long recordld ) const throw ( NoSuchRecordError );
        void writeTofile () throw ( IOError );
        const T * const addNewRecord ( T data ) throw ( MemoryError, IOError );
        void updateRecord ( T updatedRecord ) throw (IOError , NoSuchRecordError);
    public: 
        Table ( string fileName ) throw ( MemoryError ) ;
        ~Table ();
        long getNextRecordId () const ;
        const T * const getRecordForId ( long recordld ) const throw (NoSuchRecordError);
        friend class Database;
};
#endif