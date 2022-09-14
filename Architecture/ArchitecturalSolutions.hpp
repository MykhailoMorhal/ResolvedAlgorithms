


/*
	***** Task 1 *****
 
	Create structure for playing cart in game "Durak"
*/

void createPlayingCarts(const ICarts* const arg) // or unique_ptr or shred_ptr

template<typename CART>
class ICarts
{
	using PlayerNumber = uint8_t;
	ICarts(const& CART cartContainer);
public:
	virtual void createCarts() = 0;
	virtual bool isEmpty() = 0;
	std::unorderetmap<PlayerNumber,std::vector<CART>> getFirstPalyersCarts();
	std::unorderetmap<PlayerNumber,std::vector<CART>> getPalyersCarts(std::unorderetmap<PlayerNumber,CartAmount> playersMap);
protected:
	virtual void sufleCarts() = 0;
private:
};

class IGameDurak :: public ICarts
{
	virtual Cart getKozyr() = 0;
	virtual void checkIfPlayersGetCartsAtTheSameType() = 0;
}

calss DurakCarts32 :: public IGameDurak
{};


calss DurakCarts64 :: public IGameDurak
{};

struct ICart
{
	enum class CartType : uint8_t { Cherwa = 0, Buba, Pika, Chresta };
	virtual void  prepareCartsContainer() = 0;
};

struct Cart32 :: public ICart
{	
	Cart32()
	{
		prepareCartsContainer();
	}
	
	void prepareCartsContainer() ovrride
	{}
	
	std::vector<std::pair<CartType, Cart>> cartsContainer;
	enum class Cart : uint8_t
	{ Tuz = 0, King, ... };
};

class Carts64 :: public ICart
{
	// as above only has 64 carts
};

/*
	***** Task 2 *****
	
	There are 3 levels for handle events from EM(event mashine)
	If 1 level is busy this event move to 2 level. If level 2 busy
	event move to level 3. If all levels busy add event to queue
*/
 
 constexpr uint8_t EventHandlerAmount{3u};
 
class EventDispatcher
{
public:
	EventDispatcher() = default;
	
	~EventDispatcher()
	{ /* CLear all  */ }
	
	void 
	dispatchEvent(
	const Event& event, 
	std::array<std::unique_ptr<EventHandler>&, EventHandlerAmount>& eventHandlerContainer)
	{
		std::unique_ptr<EventHandler>& eventHandler = nullptr;
		do
		{
			eventHandler = eventHandlerGetter.getFreeEventHandler(eventHandlerContainer);
		}
		while(not eventHandler)
			
		if(not eventHandler.isEventProcessingSuccessful(event))
		{
			throw myhandleError::handleError( "Eevent processed unsuccessful" ); 
		}
	}
private:
	EventHandlerGetter eventHandlerGetter{};
};

class EventHandler
{
public:
	enum class EventHandlerPriorityLevel : uint8_t{ LEVEL1=1, LEVEL2, LEVEL3 };
	void getPriorityLevel() = 0;
	bool isBusy() = 0;
	bool isEventProcessingSuccessful() = 0;
private:
};

class EventHandlerLevel3 : public EventHandler{/*Do some stuf*/};
class EventHandlerLevel2 : public EventHandler{/*Do some stuf*/};
class EventHandlerLevel1 : public EventHandler{/*Do some stuf*/};

class EventHandlerGetter
{
public:
	EventHandlerGetter() = default;
	~EventHandlerGetter() = default;
	
	std::unique_ptr<EventHandler>& 
	getFreeEventHandler
	(std::array<std::unique_ptr<EventHandler>&, EventHandlerAmount>& eventHandlerContainer)
	{
		std::unique_ptr<EventHandler>& freeEventHandler = nullptr;
		if(not eventHandlerContainer.empty())
		{	
			for(const auto& elem : eventHandlerContainer)
			{
				if(not elem->isBusy())
				{
					if(not freeEventHandler)
					{
						freeEventHandler = elem;
					}
					else
					{
						freeEventHandler = (elem->getPriorityLevel() > freeEventHandler->getPriorityLevel()) ?
																					elem : freeEventHandler;
					}
				}	
			}
		}
		return freeEventHandler;
	}
};

/* 
	***** Task 3 *****
	
	Write implementation of music box 
*/

Components:

[DB Music] getMusic
[DB Music Handler] ->
[Music data] -> artist, song , type
[User Interface] -> setSerchingMusic, play, stop, next, back, repeat (EM), volume

struct MusicData
{
String author;
String name;
String albom;
String info;
};

class ITrack
{
public:
	Duration& getDuration() = 0;
	BinTypeTrack getBinTypeTrack() = 0;
	TrackInfo getTrackInfo() = 0;
private:
	Duration duration;
	BinTypeTrack ptrToBinTypeTrack;
	TrackInfo trackInfo;
};

class MusicBoxTrack : public ITrack
{
	/**/
}

class IDataBase
{
public:
	bool virtual connect() = 0;
	bool virtual disconnect() = 0;
	bool virtual isConnect() = 0;
private:
};

class MusicDataBase : public IDataBase
{
public:
	optional<ITrack> find(const MusicData& musicData){};
	
private:
};

class IUserMusicSelector
{
public:
	bool virtual up() = 0;
	bool virtual down() = 0;
	bool virtual find(const MusicData&) = 0;
private:
};

class UserMusicBoxSelector : public IUserMusicSelector
{
	/**/
};

class MusicBoxAsyncEM
{
public:
	MusicBoxEM(IUserMusicSelector userMusicBoxSelector, IUserMusicPlayer musicBoxPlayer)
	: userMusicBoxSelector(userMusicBoxSelector), musicBoxPlayer(musicBoxPlayer)
	{
		startAsyncEM();
	}
	
	bool up() 
	{ 
		state = MusicBoxAsyncEMState::UP;
		/* Do some stuff*/
	}
	
	bool down(){}
	bool stop(){}
	bool next(){}
	bool back(){}
	bool repeat(){}
	
	bool play(const InfoForUser& infoForUser)
	{
		state = MusicBoxAsyncEMState::PLAY;
		if(not musicBoxPlayer.busy())
		{
			musicBoxPlayer.play(currentTrack);
		}
		else
		{
			infoForUser = InfoGeneratorForUser::musicBoxIsBusy();
			infoForUser.pending();
		}
	}
	
	bool find(const MusicData& musicData, const InfoForUser& infoForUser)
	{
		state = MusicBoxAsyncEMState::FIND;
		bool res{false};
		auto& optionalTrack = make_shared<ITrack>(userMusicBoxSelector.find(musicData));
		if(optionalTrack.has_value())
		{
			currentTrack = optionalTrack.value();
			infoForUser = InfoGeneratorForUser::getMusicInfo(currentTrack.trackInfo());
			res = true;
		}
		else
		{
			infoForUser = InfoGeneratorForUser::cantFindMusic();
			state = MusicBoxAsyncEMState::DO_NOTHING;
		}
		return res;
	}
	
	
	
private:
	void startAsyncEM()
	{/*To do some stuff*/}

	unique_ptr<IUserMusicSelector> userMusicBoxSelector;
	unique_ptr<IUserMusicPlayer> musicBoxPlayer;
	shared_ptr<ITrack> currentTrack{nullptr};
	MusicBoxAsyncEMState state{DO_NOTHING};
	enum class MusicBoxAsyncEMState : uint8_t { PLAY = 0, STOP, NEXT, BACK, REPEAT, UP, DOWN, FIND, DO_NOTHING };
};

class InfoForUser
{};

class InfoGeneratorForUser
{};

class IUserMusicPlayer;
{
public:
	bool virtual play(shared_ptr<ITrack>&) = 0;
	bool virtual stop() = 0;
	bool virtual next(shared_ptr<ITrack>&) = 0;
	bool virtual back(shared_ptr<ITrack>&) = 0;
	bool virtual repeat(shared_ptr<ITrack>&) = 0;
private:
};
 
class MusicBoxPlayer : public IUserMusicPlayer
{
	/**/
};

/*
	***** Task 4 *****
	
	Pay Parking
*/

[Parking Place]
[Parking DB]
[Vehicle] Type, size
[UserData] Time, VehicleNumber, [Pay] 
[Vehicle Parking Handler]

class IVehicleParkingPlace
{
public:
	bool existPlace() = 0;
private:
};

class TruckParkingPlace : public IVehicleParkingPlace;
/*
 * All classes for Vehicles 
 */

class DataBase
{
public:
	bool isConnected() {/* Some Impl */}
	void prepareConnect(const DataBaseName& dbName) {/* Some Impl */}
};

class ParkingDB : public DataBase
{
	std::optional<std::unique_ptr<IVehicleParkingPlace>&> 
	getVehicleParkingPlace(const VehicleType vhType){}
	
	void registerNewPlace(const std::unique_ptr<IVehicleParkingPlace>& vehicleParkingPlacePtr, 
							const VehicleUserData& vehicleUserData) {};
};

class IDataBaseVehicleInfo
{
	/* Some Imp */
};

class ParkingDBInfo : public IDataBaseVehicleInfo
{
	/* Some Imp */
};

class VehicleParkingHandler
{
public:
	VehicleParkingHandler(const ParkingDB& parkingDB)
	: parkingDB(parkingDB)
	{}
	
	bool isSuccessfulPreparedParkingPlace
	(const unique_ptr<IVehicle> vehiclePtr, const VehicleUserData& vehicleUserData)
	{
		bool res{false};
		std::optional<std::unique_ptr<IVehicleParkingPlace>&> vehicleParkingPlace { parkingDB.getVehicleParkingPlace(vehiclePtr.getVehicleType()) };
		if(vehicleParkingPlace.has_value())
		{
			parkingDB.registerNewPlace(vehicleParkingPlace.value(), vehicleUserData);
			res = true;
		}
		return res;
	}
	
	std::optional<std::shared_ptr<IDataBaseVehicleInfo>> 
	getDBVehicleInfo(const VehicleNumber& vehicleNumber)
	{
		 return parkingDB.getVehicleInfo(vehicleNumber);	 
	}
private:
	ParkingDB& parkingDB;
};

class VehicleUserData
{
public:
	VehicleUserData(const ParkingTime& parkingTime, const VehicleNumber& vehicleNumber, const PayType payType)
	: parkingTime(parkingTime)
	, vehicleNumber(vehicleNumber)
	, payType(payType)
	{}
private:
	ParkingTime parkingTime;
	VehicleNumber vehicleNumber;
	PayType payType;
};

VehicleUtils.hpp
enum class VehicleType : uint8_t{NONE = 0; MOTOCYCLE, BUS, TRUCK, CAR3_5_TON};

class IVehicle
{
public:
	VehicleType getVehicleType() = 0;
	VehicleSize getVehicleSize() = 0;
private:
	VehicleType vehicleType{VehicleType::NONE};
	VehicleSize vehicleSize{VehicleSize::invalid};
};

class VehicleTo3_5Ton : public IVehicle
{ /* Some Imp */};

class VehicleMotocycle : public IVehicle
{ /* Some Imp */};

class VehicleFrom3_5_To_5_ton : public IVehicle
{ /* Some Imp */};

class VehicleTruck : public IVehicle
{ /* Some Imp */};


/* 
	***** Task 5 *****
	
	Online Library 
*/

Components
[Language]
	[DB library]
[User Data]
[Pay]
[Book struct]
	preferences, Autors, Type e.t.c
[Library Handler]

class DataBase
{
public:
	void connectingToDB() {/* Some Imp */}
	bool isConnected() {return isConnectedToDB}
	
private:
	bool isConnectedToDB{false};
};

class LibraryDB : public DataBase
{
public:
	std::optional<std::shared_ptr<BookReader>> getBook(const BookInfo bookInfo){/* Some Imp */}
};

class UserDB : public DataBase
{
public:
	std::optional<std::unique_ptr<UserDBInfo>> getUserDBInfo(const UserData& userData)
	{/* Some Imp */}
}

class UkLibraryDB : public LibraryDB
/*
 * For each Lenguage exist certain Library Data Base
 */
 
struct UserData
{
	std::string name{};
	std::string secondName{};
	uint64_t number{};
}
  
struct BookInfo
{
	struct Author
	{
		std::string name{};
		std::sting secondName{};
	};
	
	Author author;
	std::string bookName;
};

class UserLibraryHandler
{
public:
	LibraryHandler(const std::shared_ptr<LibraryDB> libraryDb, const std::shared_ptr<UserDB> userDb, const UserData& userData)
	{
		libraryDb = std::make_shared<LibraryDB>(libraryDb);
		userDb = std::make_shared<LibraryDB>(userDb);
		this->userData = userData;
	}
	
	bool isUserLoggedSuccessfully()
	{
		/* Some Impl */
	}
	
	bool startUserSession();
	bool checkBook();
	/*
	 * For each asynchro state exist certain method
	 */
	
	
private:
	enum class EM_STATE : uint8_t{UNDEFINE = 0, WAIT, CHECK_BOOK, SAVE_BOCK, DELETE_BOOK, READ_FROM_USER_COLLECTION, READ_FROM_GENREAL_COLLECTION, VIEW_USER_COLLECTION, SAVE_BOOK_PAGE};
	
	std::shared_ptr<LibraryDB> libraryDb;
	std::shared_ptr<UserDB> userDb;
	UserData& userData;
};

/* main class where handle all Users */
class LibraryHandler
{
public:
	/* Some Impl */
private:
	std::vector<std::unique_ptr<UserLibraryHandler>> users;
};

/*
	***** Task 6 *****
	
	Puzzls  structure
*/

[Puzzles Creator]
[Puzzles Vizualizator]
[Puzzles Driver]
[Puzzle Game]
[Struct Puzzle] -> fit left, fit right ...

/* Puzzles Utils */
using PuzzleAmount = uint64_t;
constexpr uint32_t maxLimitPuzzlesRow{100000u};
constexpr uint32_t maxLimitPuzzlesColumn{100000u};

struct Puzzle
{
	uint64_t leftSide{};
	uint64_t rightSide{};
	uint64_t upSide{};
	uint64_t downSide{};
};
/*****************/

template<uint64_t ROWS, uint64_t COLUMNS>
class PuzzlesCreator
{
public:
    PuzzlesCreator()
    {
        if((ROWS > maxLimitPuzzlesRow) or (COLUMNS > maxLimitPuzzlesColumn))
        {
            throw std::runtime_error("Too much Puzzles size");
        }
    }

    void createPuzzles()
    {
        bool isFirsPuzzleRow{true};
        
        for(PuzzleAmount i{0u}; i < ROWS; ++i)
        {
            generateUniqueKeysIndexForPuzzles(i);
        }
    }
    
    void printPuzzlesUniqueKeyIndex()
    {
        for(PuzzleAmount i{0u}; i < ROWS; ++i)
        {
            for(PuzzleAmount j{0u}; j < COLUMNS; ++j)
            {
                const auto& puzzle{puzzlesContainer.first.at(i).at(j)};
                printf("\nelem[%lu][%lu] KEYS left[%lu] up[%lu] right[%lu] down[%lu]", 
                i, j, puzzle.leftSide, puzzle.upSide, puzzle.rightSide ,puzzle.downSide);
            }
        }
    }
    
private:

    void generateUniqueKeysIndexForPuzzles(const PuzzleAmount currentRowIndex)
    {
        if(firstRowIndex == currentRowIndex)
        {
            generateUniqueKeysIndexForFirstPuzzlesRow();
        }
        else if (latestRowIndex == currentRowIndex)
        {
            generateUniqueKeysIndexForLatestPuzzlesRow();
        }
        else
        {
            generateUniqueKeysIndexForPuzzlesRow(currentRowIndex);
        }
    }
    
    void generateUniqueKeysIndexForPuzzlesRow(const PuzzleAmount currentRowIndex)
    {
        for(PuzzleAmount i{0u}; i < COLUMNS; ++i)
        {
            generateUniqueKeysIndexForPuzzleRow(currentRowIndex, i);
        }
    }
    
    void generateUniqueKeysIndexForLatestPuzzlesRow()
    {
        for(PuzzleAmount i{0u}; i < COLUMNS; ++i)
        {
            generateUniqueKeyIndexForLatestPuzzleRow(i);
        }
    }
    
    void generateUniqueKeysIndexForFirstPuzzlesRow()
    {
        for(PuzzleAmount i{0u}; i < COLUMNS; ++i)
        {
            generateUniqueKeyIndexForFirstPuzzleRow(i);
        }
    }
    
    void generateUniqueKeysIndexForPuzzleRow(const PuzzleAmount currentRowIndex, const PuzzleAmount currentColumnIndex)
    {
        const PuzzleAmount uperPuzzleIndex{currentRowIndex - 1u};
        const bool isFirstPuzzleInColumn{firstColumnIndex == currentColumnIndex};
        const bool isLatestPuzzleInColumn{latestColumnIndex == currentColumnIndex};
        auto& currentPuzzle{puzzlesContainer.first.at(currentRowIndex).at(currentColumnIndex)};
        auto& uniqueKeyIndexOfPuzzleSide{puzzlesContainer.second};
        
        if(isFirstPuzzleInColumn)
        {
            currentPuzzle.leftSide = invalidKeyIndexOfPuzzleSide;
        }
        else
        {
            const auto& previousLeftPuzzle{puzzlesContainer.first.at(currentRowIndex).at(currentColumnIndex - 1)};
            currentPuzzle.leftSide = previousLeftPuzzle.rightSide;
        }
        const auto& uperPuzzle{puzzlesContainer.first.at(uperPuzzleIndex).at(currentColumnIndex)};
        currentPuzzle.upSide = uperPuzzle.downSide;
        currentPuzzle.rightSide = isLatestPuzzleInColumn ?
            invalidKeyIndexOfPuzzleSide : ++uniqueKeyIndexOfPuzzleSide;
        currentPuzzle.downSide = ++uniqueKeyIndexOfPuzzleSide;
    }
    
    void generateUniqueKeyIndexForLatestPuzzleRow(const PuzzleAmount currentColumnIndex)
    {
        const PuzzleAmount uperPuzzleIndex{latestRowIndex - 1u};
        auto& currentPuzzle{puzzlesContainer.first.at(latestRowIndex).at(currentColumnIndex)};
        auto& uniqueKeyIndexOfPuzzleSide{puzzlesContainer.second};
        const bool isFirstPuzzleInRow{firstColumnIndex == currentColumnIndex};
        const bool isLatestPuzzleInLatestRow{latestColumnIndex == currentColumnIndex};
        
        if(isFirstPuzzleInRow)
        {
            currentPuzzle.leftSide = invalidKeyIndexOfPuzzleSide;
        }
        else
        {
            const auto& previousLeftPuzzle{puzzlesContainer.first.at(latestRowIndex).at(currentColumnIndex - 1)};
            currentPuzzle.leftSide = previousLeftPuzzle.rightSide;
        }
        const auto& uperPuzzle{puzzlesContainer.first.at(uperPuzzleIndex).at(currentColumnIndex)};
        currentPuzzle.upSide = uperPuzzle.downSide;
        currentPuzzle.rightSide = isLatestPuzzleInLatestRow ?
            invalidKeyIndexOfPuzzleSide : ++uniqueKeyIndexOfPuzzleSide;
        currentPuzzle.downSide = invalidKeyIndexOfPuzzleSide;
            
    }
    
    void generateUniqueKeyIndexForFirstPuzzleRow(const PuzzleAmount currentColumnIndex)
    {
        auto& currentPuzzle{puzzlesContainer.first.at(firstRowIndex).at(currentColumnIndex)};
        auto& uniqueKeyIndexOfPuzzleSide{puzzlesContainer.second};
        const bool isFirstPuzzleInFirstRow{firstColumnIndex == currentColumnIndex};
        const bool isLatestPuzzleInRow{latestColumnIndex == currentColumnIndex};
        
        if(isFirstPuzzleInFirstRow)
        {
            currentPuzzle.leftSide = invalidKeyIndexOfPuzzleSide;
        }
        else
        {
            const auto& previousLeftPuzzle{puzzlesContainer.first.at(firstRowIndex).at(currentColumnIndex - 1)};
            currentPuzzle.leftSide = previousLeftPuzzle.rightSide;
        }
        currentPuzzle.upSide = invalidKeyIndexOfPuzzleSide;
        currentPuzzle.rightSide = isLatestPuzzleInRow ? 
            invalidKeyIndexOfPuzzleSide : ++uniqueKeyIndexOfPuzzleSide;
        currentPuzzle.downSide = ++uniqueKeyIndexOfPuzzleSide;
    }

using UniqueKeyIndexOfPuzzleSide = uint64_t;
using PuzzlesContainer = std::pair<std::array<std::array<Puzzle, ROWS>, COLUMNS>,UniqueKeyIndexOfPuzzleSide>;
PuzzlesContainer puzzlesContainer{};
const PuzzleAmount latestColumnIndex{COLUMNS - 1u};
const uint8_t firstColumnIndex{0u};
const PuzzleAmount latestRowIndex{ROWS - 1u};
const uint8_t firstRowIndex{0u};
const uint64_t invalidKeyIndexOfPuzzleSide{0u};
};

class PuzzlesHandler
{ 
/* Implementation */
// .
// .
	void updateGameAfterSetCoordinate()
	{
		if(fitsWith())
		{
			updateCollectedPuzzlesMap();
		}
		else
		{
			informUserAboutWrongPuzzlesChoise();
		}
	}
};
class PuzzlesCoordinates
{ /* Implementation */ }

template<uint64_t ROWS, uint64_t COLUMNS>
class PuzzleGame
{
public:
	PuzzleGame(PuzzlesCoordinates& puzzlesCoordinates)
	{
		auto& puzzlesContainerFromCreator {PuzzlesCreator<ROWS,COLUMNS>::createPuzzles()};
		puzzlesHandler.setPuzzles(std::move(puzzlesContainerFromCreator));
		const auto& puzzlesContainer = puzzlesHandler.getPuzzles();
		this->puzzlesCoordinates = puzzlesCoordinates;
		this->puzzlesCoordinates.setPuzzles(puzzlesContainer);
	}
	
	void startGame()
	{
		puzzlesHandler.showPuzzles();
		gameProcess();
	}
	
private:
	void gameProcess()
	{
		while(not puzzlesHandler.isAllPuzzlesHandled())
		{
			
			const auto& puzzleCoordinate {puzzlesCoordinates.getPuzzleCoordinatesFromUser()};
			puzzlesHandler.setPuzzleCoordinate(puzzleCoordinate);
			puzzlesHandler.updateGameAfterSetCoordinate();
		}	
	}
		
	PuzzlesHandler puzzlesHandler{};
	PuzzlesCoordinates& puzzlesCoordinates;
};

/* 
	***** Task 7 *****
	
	Chat servrer 
*/

Backend
	Serever consist of several fisical PC.Avoid narrow place(don't keep User logo in one PC)
	[ChatSystem]
		[User DB]
		[Update System] or [Critical error]
			[Switch between System]
			[Temporary Chat Clon]
		[NetworkConnector]
			[UserNetworkConnector]
			[SystemNetworkConnector]
		[UserLoogin]
		[Chat]
			[SM]
				[UserAddDataToChat, CheckData, WaitToAction, DeleteLegasyData]
			[MediaSaver]
			[UsersMsgsBuffer]
				[queue FIFO]
		[UserDataHandlerFromNetwork]
			[UserDataDecoder]
				[Music, Picture, Video]
		
class IDataBase
{
public:
	void connecting() = 0;
	bool isConnected() = 0;
private:
	void process() = 0;
	/* Impl */
};

class UserDB : public IDataBase
{ /* Impl */ };

class ChatDB : public IDataBase
{ /* Impl */ };

class IDataBuffer
{
public:
	void initBuffer();
	bool isBufferStatusOK();
	bool isBufferEmpty();
	void setDataToBuffer() = 0;
	void getDataFromBuffer() = 0;
	void eraseData() = 0;
private:
	RawDataBuffer rawDataBuffer;
};

class BufferDataFromUserChat : public IDataBuffer
{ /* Impl */ };

class ClonBuffer
{
public:
	ClonBuffer()
	{
		initBuffer();
	}
	
	bool isBufferStatusOK()
	{/* Impl */}
	
	void copyUsersDateFromChat(std::shared_ptr<BufferDataFromUserChat>)
	{ /* Impl */ }
private:
	enum class BUFFER_STATUS uint8_t { NOT_OK=0, OK };
	
	void initBuffer()
	{/* Impl */}
	
	bool bufferStatuts{NOT_OK};
};

class UserChatClon
{
public:
	UserChatClon(std::unique_ptr<UserChat>& userChat)
	: userChat(userChat)
	{
		clonBuffer.init();
		startCloneProcess();
	}
	
	void startProcessInsteadUserChat()
	{ /* Init */ }
private:
	void startCloneProcess()
	{
		while(clonBuffer.isBufferStatusOK())
		{
			if(userChat.hasNewChatUserDate())
			{
				clonBuffer.copyUsersDateFromChat(userChat.getNewUsersDateFromChat());
			}
		}
	}

	std::unique_ptr<MainUserChat>& userChat;
	std::unique_ptr<ClonBuffer> clonBuffer{};
};

class INetworkConnector
{
public:
	INetworkConnector()
	{
		initConnectionWithMainNetworkPage();
	}
	
	bool isConnectionOK() = 0;
	void closeAllConnections() = 0;
	
private:
	bool isConnectionWithMainNetworkPageOK()
	{/* Init */}

	void initConnectionWithMainNetworkPage()
	{/* Init */}
};

class StreamBuffer
{ /* Impl */ } 

class SystemNetworkConnector : public INetworkConnector
{
public:
	void connectToSystemNetworkPage(){ /* Impl */ }
	std::share_ptr<StreamBuffer> getSystemStreamBuffer(){/* Impl */}
private:
	StreamBuffer streamBuffer{};
};

class UserNetworkConnector : public INetworkConnector
{
public:
	void connectToUserNetwork(){ /* Impl */ }
	std::share_ptr<StreamBuffer> getSystemStreamBuffer(){/* Impl */}
private:
	StreamBuffer streamBuffer{};
};

class SwitcherToChatClone
{
public:
private:
};

class Chat
{
public:
	Chat(const std::unique_ptr<SwitcherToChatClone>& switcherToChatClone)
	: switcherToChatClone = switcherToChatClone
	, userDataNetworkHandler = userDataNetworkHandler
	{
		initializationChat();
		startChatProcess();
	}
	
	void startChatProcess()
	{
		logAllActiveUsers();
		informAllActiveUsersAboutSuccessLogin();
		startReceiveChatUserData();
	}
	
private:
	void startReceiveChatUserData()
	{
		while(switcherToChatClone.notNeed())
		{
			if(isLoginNewUsers())
			{
				handleNewUsers();
			}
			
			chatState = HANDLE_NEW_DATA_FROM_USERS;
			if(not isSuccessedWriteDataToChatBuffer())
			{
				chatState = INVALID_DATA_FROM_USERS;
				cantWriteDataToBufferWrning();
			}
			
			if(needConvertMultimediaData())
			{
				convertMultimediaData();
			}
			
			if(needPushDataToChat())
			{
				pushDataToChat();
			}
		}
	}
	
	void convertMultimediaData()
	{
		chatState = HANDLE_MULTIMEDIA_DATA_FROM_USERS;
		userDataMultimediaConverter.addRawMultimediaData(bufferDataFromUserChat.getRawMultimediaData());
		userDataMultimediaConverter.convertData();
	}
	
	bool needConvertMultimediaData()
	{
		return bufferDataFromUserChat.hasMultimediaData();
	}
	
	bool isSuccessedWriteDataToUserBuffer()
	{
		return bufferDataFromUserChat.pushData(userDataNetworkHandler.getBufferedUsersChatData());
	}
	
	void handleNewUsers()
	{
		chatState = LOGIN_USERS;
		const auto& newUsersLoginData{userDataNetworkHandler.getNewActiveUsers()};
		findUsersInDB(usersLoginData);
	}
	
	bool isLoginNewUsers()
	{
		return userDataNetworkHandler.isLoginNewUsers();
	}
	
	bool needPushDataToChat()
	{
		return bufferDataFromUserChat.needPushDataToChat();
	}

	void informAllActiveUsersAboutSuccessLogin()
	{
		for(const auto&[ , currentUser] : activeUsers)
		{
			currentUser.informLoginSuccess();
		}	
	}

	void logAllActiveUsers()
	{
		chatState = LOGIN_USERS;
		printCurrentState();
		const auto& usersLoginData{userDataNetworkHandler.getAllActiveUsers()};
		findUsersInDB(usersLoginData);
	}
	
	void findUsersInDB(const std::vector<UserLoginData>& usersLoginData)
	{
		for(const auto& currentUser : usersLoginData)
		{
			if(findUserInDB(currentUser))
			{
				addUserToActiveUserList(currentUser);
			}
			else
			{
				cantFindUserInDBWarning(currentUser);
			}
		}
	}
	
	void addUserToActiveUserList(const UserLoginData& userLoginData)
	{
		activeUsers.emplace(std::make_pair(userLoginData.getID(),userLoginData.getUserConnectionData()));
	}
	
	void triggerWarningCantFindUser(const UserLoginData& userLoginData)
	{
		LG_WRN("User don't register in DB");
		userLoginData.informUserAboutFailingLogin();
	}
	
	bool findUserInDB(const UserLoginData& userLoginData)
	{
		return userDB.find(userLoginData);
	}

	void initializationChat()
	{
		chatState = INITIALIZATION;
		printCurrentState();
		userDB.connecting();
		chatDB.connecting();
		userLoogin.init();
	}

	enum class uint8_t CHAT_EM { HANDLE_NEW_DATA_FROM_USERS = 0, INVALID_DATA_FROM_USERS, WAIT_TO_ACTION, 
								DELETE_ABSOLIT_CHAT_DATA, PUSH_DATA_TO_CHAT, LOGIN_USERS, INITIALIZATION, HANDLE_MULTIMEDIA_DATA_FROM_USERS };
	std::unique_ptr<UserDataHandlerFromNetwork>& userDataNetworkHandler{};
	std::unique_ptr<SwitcherToChatClone>& switcherToChatClone;
	UserLoogin userLoogin{};
	BufferDataFromUserChat bufferDataFromUserChat{};
	std::unordered_map<UserConnectionData> activeUsers{};
	UserDataMultimediaConverter userDataMultimediaConverter{};
	UserDB userDB{};
	ChatDB chatDB{};
	CHAT_EM chatState;
};

/* 
	***** Task 8 *****
	
	File System Structure
*/

[File System]
	getFile
	setFile
	descriptorsContainer
	getAmountOfFilledMemory
	getAmountOfFreedMemory
	
	FilesHandler
		delete
		add
		
		MemoryClaster
			getMemoryPool(size)
		File
			Name
			Atributes
			Size
			Location
		Folder
			Name
			Atributes
			Size
			Location
			File/Folder

class IFileSystem
{
public:
private:	
};