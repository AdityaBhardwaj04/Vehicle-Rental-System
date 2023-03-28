#include "table.h"
#include <iostream>
using namespace std;
template <class T> Table<T> :: Table ( string filename ) throw( MemoryError ) {
    this->fileName = fileName;
    this->records = new vector<Storable*>();
    if(!this->records){
        throw MemoryError;
    }
}
template <class T> long Table<T> :: getNextRecordId() const{
    return this->records->size() + 1;
}
template <class T> const T * const Table<T> :: addNewRecord ( T record)
throw ( MemoryError, IOError ) {
    T * newRecord = new T ( record ) ;
    if ( !newRecord ) {
        throw new MemoryError() ;
    }
    newRecord->recordId = this->getNextRecordId();
    this->records->push_back(newRecord);
    try{
        this->writeTofile();
    }
    catch (IOError error){
        this->records->pop_back();
        delete newRecord;
        throw;
    }
}
template <class T> void Table<T> :: updateRecord ( T updatedRecord ) throw( IOError, NoSuchRecordError ){
    for ( auto & record : *this- >records ){
        if ( record->getRecordId ( ) == updatedRecord . getRecordId() ) {
            T * pointerToRecord = dynamic_cast<T*>(record);
            if(pointerToRecord){
                T oldRecord = T ( *pointerToRecord );
                record->setDataFrotn ( &updatedRecord );
                try{
                    this->writeTofi1e();
                    return;
                }
                catch (IOError error){
                    record->setDataFrom(&oldRecord);
                    throw;
                }
            }
        }
    }
    throw NoSuchRecordError();
}
template <class T> void Table<T> :: writeTofile() throw (IOError){
    this->fileStream.open(fileName, ios::out | ios::trunc);
    if(!this->fileStream){
        throw IOError();
    }
    for(auto & record : *records){
        fileStream << record->toString() << endl;
    }
    this->fileStream.close();
}

template <class T> const T * const Table<T> :: getRecordForId(long recordId) const throw (NoSuchRecordError){
    try{
        return this->getReferenceOfRecordForId(recordId);
    }
    catch(NoSuchRecordError error){
        throw;
    }
}
template <class T> T * Table<T> :: getReferenceOfRecordForId(long recordId) const throw(NoSuchRecordError){
    for(auto & record : *records){
        if(record->getRecordId() == recordId){
            return dynamic_cast<T*> (record);
        }
    }
    throw NoSuchRecordError();
}
template <class T> Table<T> :: ~Table(){
    for(auto & record : *records){
        delete dynamic_cast<T*> (record);
    }
    this->records->clear();
    this->records->shrink_to_fit();
    delete this->records;
}