
#ifndef __FILEIO_H
#define __FILEIO_H

#include <cstdio>
#include <cstdlib>
#include <string>

class UOXFile;
class BinBuffer;

#ifndef __UOX3_H
#include "uox3.h"
#endif

#ifndef __CLASSES_H
#include "classes.h"
#endif

using namespace std;

class UOXFile
{
private:

	int			fmode, bSize, bIndex;
	bool		ok;
	UI08 *		ioBuff;
	FILE *		theFile;

public:

				UOXFile( const char *, char * );
	virtual		~UOXFile();

	inline int	qRefill( void ) { return( bIndex >= bSize ); };
	inline int	ready( void ) { return( ok ); };
	void		rewind( void );
	void		seek( long, int );
	inline int	eof( void ) { return ( feof( theFile ) ); };
	int			getch( void );
	void		refill( void );

	char *		gets( char *, int );
	int			puts( char * );
	
	void		getUChar( UI08 *, UI32 );
	void		getUChar( UI08 *c ) { getUChar( (UI08 *) c, 1 ); }

	void		getChar( SI08 *, UI32 );
	void		getChar( SI08 *c) { getChar( c, 1 ); }

	void		getUShort( UI16 *, UI32 = 1 );
	void		getShort( SI16 *, UI32 = 1 );
	void		getULong( UI32 *, UI32 = 1 );
	void		getLong( SI32 *, UI32 = 1 );

	void		get_versionrecord( struct versionrecord *, UI32 = 1 );
	void		get_st_multi( struct st_multi *, UI32 = 1 );
	void		get_land_st( CLand *, UI32 = 1 );
	void		get_tile_st( CTile *, UI32 = 1 );
	void		get_map_st( struct map_st *, UI32 = 1 );
	void		get_st_multiidx( struct st_multiidx *, UI32 = 1 );
	void		get_staticrecord( struct staticrecord *, UI32 = 1 );

	int			getLength( void );
};

class BinBuffer
{
public:
	BinBuffer();
	BinBuffer( ifstream & );
	~BinBuffer();

	void Read( ifstream & );
	void Write( ofstream & );
	void Reset( void );

	UI32 Size( void );
	UI08 GetType( void );
	void SetType( UI08 );

	UI08 GetByte( void );
	void PutByte( UI08 );
	SI16 GetShort( void );
	void PutShort( SI16 );
	SI32 GetLong( void );
	void PutLong( SI32 );
	R32 GetFloat( void );
	void PutFloat( R32 );

	void PutStr( const char * );
	int GetStr( char *, int = 255 );

	void Put( const void *, int );
	void Get( void *, int );

	bool End( void );

	int Position( void );
	int Length( void );

protected:
	vector<char> Buff;
	int fp;
	UI08 myType;
};

#endif
