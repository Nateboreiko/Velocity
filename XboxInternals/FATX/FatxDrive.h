#ifndef FATXDRIVE_H
#define FATXDRIVE_H

#include "../Stfs/StfsDefinitions.h"

#include "../IO/DeviceIO.h"
#include "../IO/FatxIO.h"
#include "../Cryptography/XeKeys.h"
#include "FatxConstants.h"

class XBOXINTERNALSSHARED_EXPORT FatxDrive
{

public:
    FatxDrive(std::string drivePath);
    FatxDrive(std::wstring drivePath);
    ~FatxDrive();

    // get the drives partitions
    std::vector<Partition*> GetPartitions();

    // get a FatxIO for the given entry
    FatxIO GetFatxIO(FatxFileEntry *entry);

    // populate entry's cachedFiles vector (only if it's a directory)
    void GetChildFileEntries(FatxFileEntry *entry);

    // populate entry's clusterChain with its cluster chain
    void ReadClusterChain(FatxFileEntry *entry);

    // save the security blob to local disk
    void ExtractSecurityBlob(std::string path);

    // writes the 'newEntry' to disk, in the 'parent' folder
    void CreateFileEntry(FatxFileEntry *parent, FatxFileEntry *newEntry);

    // get the first 4 bytes of a file
    void GetFileEntryMagic(FatxFileEntry *entry);

    // deletes the entry and all of it's children
    void DeleteFile(FatxFileEntry *entry);

    // inject the file
    void InjectFile(FatxFileEntry *parent, std::string name, std::string filePath);

    // close the underlying io
    void Close();

    // convert a cluster to an offset
    static INT64 ClusterToOffset(Partition *part, DWORD cluster);

    SecurityInfo securityBlob;

private:
    // open up a physical drive
    void loadFatxDrive(std::wstring drivePath);

    // process a partition and load it with calulated information
    void processBootSector(Partition *part);

    // counts the largest amount of consecutive unset bits
    static BYTE cntlzw(DWORD x);

    DeviceIO *io;
    std::vector<Partition*> partitions;
};

#endif // FATXDRIVE_H
