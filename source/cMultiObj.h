#ifndef __CMULTIOBJ_H__
#define __CMULTIOBJ_H__


class CMultiObj : public CItem
{
protected:
	std::string			deed;

	std::map< CChar *, UI08 >	housePrivList;

	ITEMLIST			lockedList;
	UI16				maxLockdowns;

	ITEMLIST			secureContainerList;
	UI16				maxSecureContainers;

	ITEMLIST			trashContainerList;
	UI16				maxTrashContainers;

	CHARLIST			vendorList;
	UI16				maxVendors;

	UI16				maxFriends;
	UI16				maxGuests;
	UI16				maxOwners;
	UI16				maxBans;

	SI16				banX;
	SI16				banY;

	bool				isPublic;
	UI16				numberOfVisits;

	time_t				buildTimestamp;
	time_t				tradeTimestamp;

	virtual bool		LoadRemnants( void ) override;

	CDataList< CItem * >	itemInMulti;
	CDataList< CChar * >	charInMulti;
	CDataList< CChar * >	ownersOfMulti;
	CDataList< CChar * >	friendsOfMulti;
	CDataList< CChar * >	bannedFromMulti;
	CDataList< CChar * >	guestsOfMulti;

public:
	CMultiObj();
	virtual				~CMultiObj();

	// Banlist
	void				AddToBanList( CChar *toBan );
	void				RemoveFromBanList( CChar *toRemove );
	void				ClearBanList( void );
	UI16				GetBanCount( void );
	UI16				GetMaxBans( void ) const;
	void				SetMaxBans( UI16 newValue );

	// Owner/CoOwnerlist
	void				AddAsOwner( CChar *newOwner );
	void				RemoveAsOwner( CChar *toRemove );
	void				ClearOwnerList( void );
	UI16				GetOwnerCount( void );
	UI16				GetMaxOwners( void ) const;
	void				SetMaxOwners( UI16 newValue );

	// Friendlist
	void				AddAsFriend( CChar *newFriend );
	void				RemoveAsFriend( CChar *toRemove );
	void				ClearFriendList( void );
	UI16				GetFriendCount( void );
	UI16				GetMaxFriends( void ) const;
	void				SetMaxFriends( UI16 newValue );

	// Guestlist (not saved)
	void				AddAsGuest( CChar *newGuest );
	void				RemoveAsGuest( CChar *toRemove );
	void				ClearGuestList( void );
	UI16				GetGuestCount( void );
	UI16				GetMaxGuests( void ) const;
	void				SetMaxGuests( UI16 newValue );

	// Lockdowns
	size_t				GetLockdownCount( void ) const;
	UI16				GetMaxLockdowns( void ) const;
	void				SetMaxLockdowns( UI16 newValue );
	void				LockDownItem( CItem *toLock );
	void				ReleaseItem( CItem *toRemove );

	// Secure Containers
	size_t				GetSecureContainerCount( void ) const;
	UI16				GetMaxSecureContainers( void ) const;
	void				SetMaxSecureContainers( UI16 newValue );
	bool				IsSecureContainer( CItem *toCheck );
	void				SecureContainer( CItem *toSecure );
	void				UnsecureContainer( CItem *toUnsecure );

	// Trash Containers
	size_t				GetTrashContainerCount( void ) const;
	UI16				GetMaxTrashContainers( void ) const;
	void				SetMaxTrashContainers( UI16 newValue );
	void				AddTrashContainer( CItem *toAdd );
	void				RemoveTrashContainer( CItem *toRemove );

	// Player Vendor list
	size_t				GetVendorCount( void ) const;
	UI16				GetMaxVendors( void ) const;
	void				SetMaxVendors( UI16 newValue );
	void				AddVendor( CChar *toAdd );
	void				RemoveVendor( CChar *toRemove );

	bool				IsOnBanList( CChar *toBan ) const;
	bool				IsOnFriendList( CChar *toCheck ) const;
	bool				IsOnGuestList( CChar *toCheck ) const;
	bool				IsOnOwnerList( CChar *toCheck ) const;
	bool				CheckForAccountCoOwnership( CChar *toCheck ) const;
	bool				IsOwner( CChar *toFind ) const;

	void				AddToMulti( CBaseObject *toAdd );
	void				RemoveFromMulti( CBaseObject *toRemove );

	bool				GetPublicStatus( void ) const;
	void				SetPublicStatus( const bool newBool );

	SI16				GetBanX( void ) const;
	void				SetBanX( const SI16 newVal );
	SI16				GetBanY( void ) const;
	void				SetBanY( const SI16 newVal );

	UString				GetBuildTimestamp( void ) const;
	void				SetBuildTimestamp( time_t newTime );
	UString				GetTradeTimestamp( void ) const;
	void				SetTradeTimestamp( time_t newTime );

	virtual bool		Save( std::ofstream &outStream ) override;
	virtual bool		DumpHeader( std::ofstream &outStream ) const override;
	virtual bool		DumpBody( std::ofstream &outStream ) const override;
	virtual bool		HandleLine( UString &UTag, UString &data ) override;

	virtual void		SetOwner( CChar *newOwner ) override;

	std::string			GetDeed( void ) const;
	void				SetDeed( const std::string &newDeed );

	virtual void		Cleanup( void ) override;

	virtual bool		CanBeObjType( ObjectType toCompare ) const override;

	CDataList< CChar * > *	GetOwnersOfMultiList( bool clearList = false );
	CDataList< CChar * > *	GetFriendsOfMultiList( bool clearList = false );
	CDataList< CChar * > *	GetGuestsOfMultiList( bool clearList = false );
	CDataList< CChar * > *	GetBannedFromMultiList( bool clearList = false );
	CDataList< CChar * > *	GetCharsInMultiList( void );
	CDataList< CItem * > *	GetItemsInMultiList( void );

};

class CBoatObj : public CMultiObj
{
protected:
	SERIAL				tiller;
	SERIAL				planks[2];
	SERIAL				hold;
	UI08				moveType;

	TIMERVAL			nextMoveTime;

private:
	virtual bool		DumpHeader( std::ofstream &outStream ) const override;
	virtual bool		DumpBody( std::ofstream &outStream ) const override;

	virtual bool		HandleLine( UString &UTag, UString &data ) override;

public:
	CBoatObj();
	virtual				~CBoatObj();

	SERIAL				GetTiller( void ) const;
	SERIAL				GetPlank( UI08 plankNum ) const;
	SERIAL				GetHold( void ) const;
	UI08				GetMoveType( void ) const;

	void				SetPlank( UI08 plankNum, SERIAL newVal );
	void				SetTiller( SERIAL newVal );
	void				SetHold( SERIAL newVal );
	void				SetMoveType( UI08 newVal );

	TIMERVAL			GetMoveTime( void ) const;
	void				SetMoveTime( TIMERVAL newVal );

	virtual bool		CanBeObjType( ObjectType toCompare ) const override;
};

#endif

