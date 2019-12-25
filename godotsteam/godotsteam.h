#ifndef GODOTSTEAM_H
#define GODOTSTEAM_H
// Include INT types header
#include <inttypes.h>
// Include Steamworks API header
#include "steam/steam_api.h"
// Include Godot headers
#include "core/object.h"
#include "scene/resources/texture.h"
#include "core/reference.h"
#include "core/dictionary.h"

class Steam: public Object {
	GDCLASS(Steam, Object);

	public:
		enum {
			OFFLINE=0, ONLINE=1, BUSY=2, AWAY=3, SNOOZE=4, LF_TRADE, LF_PLAY, STATE_MAX, NOT_OFFLINE=8, ALL=9,
			TOP_LEFT=0, TOP_RIGHT=1, BOT_LEFT=2, BOT_RIGHT=3,
			FLAG_NONE=0x00, FLAG_BLOCKED=0x01, FLAG_FRIENDSHIP_REQUESTED=0x02, FLAG_IMMEDIATE=0x04, FLAG_CLAN_MEMBER=0x08, FLAG_ON_GAME_SERVER=0x10, FLAG_REQUESTING_FRIENDSHIP=0x80, FLAG_REQUESTING_INFO=0x100,
			FLAG_IGNORED=0x200, FLAG_IGNORED_FRIEND=0x400, FLAG_CHAT_MEMBER=0x1000, FLAG_ALL=0xFFFF,	
			OK=0, FAILED=1, ERR_NO_CLIENT=2, ERR_NO_CONNECTION=3,
			RELATION_NONE=0, RELATION_BLOCKED=1, RELATION_REQUEST_RECIPIENT=2, RELATION_FRIEND=3, RELATION_REQUEST_INITIATOR=4, RELATION_IGNORED=5, RELATION_IGNORED_FRIEND=6, RELATION_SUGGESTED=7, RELATION_MAX=8,
			AUTH_SESSION_OK=0, AUTH_SESSION_STEAM_NOT_CONNECTED=1, AUTH_SESSION_NO_LICENSE=2, AUTH_SESSION_VAC_BANNED=3, AUTH_SESSION_LOGGED_IN_ELSEWHERE=4,
			AUTH_SESSION_VAC_CHECK_TIMEOUT=5, AUTH_SESSION_TICKET_CANCELED=6, AUTH_SESSION_TICKET_ALREADY_USED=7, AUTH_SESSION_TICKET_INVALID=8, AUTH_SESSION_PUBLISHER_BANNED=9,
			AVATAR_SMALL=0, AVATAR_MEDIUM, AVATAR_LARGE,
			GLOBAL=0, GLOBAL_AROUND_USER=1, FRIENDS=2, USERS=3,
			PERSONA_NAME_MAX_UTF16=128, PERSONA_NAME_MAX_UTF8=128,
			PERSONA_CHANGE_NAME=0x0001, PERSONA_CHANGE_STATUS=0x0002, PERSONA_CHANGE_COME_ONLINE=0x0004, PERSONA_CHANGE_GONE_OFFLINE=0x0008, PERSONA_CHANGE_GAME_PLAYED=0x0010, PERSONA_CHANGE_GAME_SERVER=0x0020, PERSONA_CHANGE_AVATAR=0x0040, PERSONA_CHANGE_JOINED_SOURCE=0x0080,
			PERSONA_CHANGE_LEFT_SOURCE=0x0100, PERSONA_CHANGE_RELATIONSHIP_CHANGED=0x0200, PERSONA_CHANGE_NAME_FIRST_SET=0x0400, PERSONA_CHANGE_FACEBOOK_INFO=0x0800, PERSONA_CHANGE_NICKNAME=0x1000, PERSONA_CHANGE_STEAM_LEVEL=0x2000,
			RESTRICTION_NONE=0, RESTRICTION_UNKNOWN=1, RESTRICTION_ANY_CHAT=2, RESTRICTION_VOICE_CHAT=4, RESTRICTION_GROUP_CHAT=8, RESTRICTION_RATING=16, RESTRICTION_GAME_INVITES=32, RESTRICTION_TRADING=64,
			CHAT_INVALID=0, CHAT_MESSAGE=1, CHAT_TYPING=2, CHAT_INVITE_GAME=3, CHAT_EMOTE=4, CHAT_LEFT=6, CHAT_ENTERED=7, CHAT_KICKED=8, CHAT_BANNED=9, CHAT_DISCONNECTED=10, CHAT_HISTORICAL=11, CHAT_LINK_BLOCKED=14,
			CHAT_METADATA_MAX=8192, MAX_RICH_PRESENCE_KEYS=20, MAX_RICH_PRESENCE_KEY_LENGTH=64, MAX_RICH_PRESENCE_VALUE_LENGTH=256,
			OVERLAY_TO_STORE_FLAG_NONE=0, OVERLAY_TO_STORE_FLAG_ADD_TO_CART=1, OVERLAY_TO_STORE_FLAG_ADD_TO_CART_AND_SHOW=2,
			LOBBY_OK=0, LOBBY_NO_CONNECTION=1, LOBBY_TIMEOUT=2, LOBBY_FAIL=3, LOBBY_ACCESS_DENIED=4, LOBBY_LIMIT_EXCEEDED=5,
			PRIVATE=0, FRIENDS_ONLY=1, PUBLIC=2, INVISIBLE=3, LOBBY_KEY_LENGTH=255,
			EP2P_SEND_UNRELIABLE = 0, EP2P_SEND_UNRELIABLE_NO_DELAY = 1, EP2P_SEND_RELIABLE = 2, EP2P_SEND_RELIABLE_WITH_BUFFERING = 3,
			LOBBY_EQUAL_LESS_THAN=-2, LOBBY_LESS_THAN=-1, LOBBY_EQUAL=0, LOBBY_GREATER_THAN=1, LOBBY_EQUAL_GREATER_THAN=2, LOBBY_NOT_EQUAL=3,
			LOBBY_DISTANCE_CLOSE=0, LOBBY_DISTANCE_DEFAULT=1, LOBBY_DISTANCE_FAR=2, LOBBY_DISTANCE_WORLDWIDE=3,
			UGC_PREVIEW_TYPE_IMAGE=0, UGC_PREVIEW_TYPE_YOUTUBE=1, UGC_PREVIEW_TYPE_SKETCHFAB=2, UGC_PREVIEW_TYPE_ENVIRONMENT_MAP_HORIZONTALCROSS=3, UGC_PREVIEW_TYPE_ENVIRONMENT_MAP_LATLONG=4, UGC_PREVIEW_TYPE_RESERVED_MAX=255,
			UGC_NUM_RESULTS_PER_PAGE=50, UGC_DEVELOPER_METADATA_MAX=5000, UGC_QUERY_HANDLE_INVALID=0ULL, UGC_UPDATE_HANDLE_INVALID=0ULL, UGC_MAX_TITLE_CHARS=128, UGC_MAX_DESC_CHARS=5000, UGC_MAX_METADATA_CHARS=5000,
			UGC_STATE_NONE=0, UGC_STATE_SUBSCRIBED=1, UGC_STATE_LEGACY=2, UGC_STATE_INSTALLED=4, UGC_STATE_UPDATE=8, UGC_STATE_DOWNLOADING=16, UGC_STATE_PENDING=32,
			UGC_STATS_SUBSCRIPTIONS=0, UGC_STATS_FAVORITES=1, UGC_STATS_FOLLOWERS=2, UGC_STATS_UNIQUE_SUBSCRIPTIONS=3, UGC_STATS_UNIQUE_FAVORITES=4, UGC_STATS_UNIQUED_FOLLOWERS=5, UGC_STATS_UNIQUE_VIEWS=6, UGC_STATS_SCORE=7, UGC_STATS_SECONDS_PLAYED=8, UGC_STATS_PLAYTIME_SESSIONS=9,
			UGC_STATS_COMMENTS=10, UGC_STATS_SECONDS_PLAYED_DURING_PERIOD=11, UGC_STATS_PLAYTIME_SESSIONS_DURING_PERIOD=12,
			UGC_STATUS_INVALID=0, UGC_STATUS_PREPARING_CONFIG=1, UGC_STATUS_PREPARING_CONTENT=2, UGC_STATUS_UPLOADING_CONTENT=3, UGC_STATUS_UPLOADING_PREVIEW=4, UGC_STATUS_COMMITTING_CHANGES=5,
			UGC_MATCH_ITEMS=0, UGC_MATCH_ITEMS_MTX=1, UGC_MATCH_ITEMS_READYTOUSE=2, UGC_MATCH_COLLECTIONS=3, UGC_MATCH_ARTWORK=4, UGC_MATCH_VIDEOS=5, UGC_MATCH_SCREENSHOTS=6, UGC_MATCH_ALLGUIDES=7, UGC_MATCH_WEBGUIDES=8, UGC_MATCH_INTEGRATEDGUIDES=9, UGC_MATCH_USABLE_INGAME=10,
			UGC_MATCH_CONTROLLER_BINDINGS=11, UGC_MATCH_GAMEMANAGED_ITEM=12, UGC_MATCH_ALL=0,
			UGC_QUERY_RANKED_VOTE=0, UGC_QUERY_RANKED_PUBLICATION_DATE=1, UGC_QUERY_RANKED_ACCEPTANCE_DATE=2, UGC_QUERY_RANKED_TREND=3, UGC_QUERY_RANKED_FRIEND_FAVORITE=4, UGC_QUERY_RANKED_FRIEND_CREATED=5, UGC_QUERY_RANKED_TIMES_REPORTED=6, UGC_QUERY_RANKED_FOLLOWED_USERS=7,
			UGC_QUERY_RANKED_NOT_RATED=8, UGC_QUERY_RANKED_TOTAL_VOTES_ASC=9, UGC_QUERY_RANKED_VOTES_UP=10, UGC_QUERY_RANKED_TEXT_SEARCH=11, UGC_QUERY_RANKED_UNIQUE_SUBSCRIPTIONS=12, UGC_QUERY_RANKED_PLAYTIME_TREND=13, UGC_QUERY_RANKED_TOTAL_PLAYTIME=14, UGC_QUERY_RANKED_AVERAGE_PLAYTIME=15,
			UGC_QUERY_RANKED_LIFETIME_AVERAGE_PLAYTIME=16, UGC_QUERY_RANKED_PLAYTIME_SESSION=17, UGC_QUERY_RANKED_LIFETIME_PLAYTIME=18,
			UGC_LIST_PUBLISHED=0, UGC_LIST_VOTED_ON=1, UGC_LIST_VOTED_UP=2, UGC_LIST_VOTED_DOWN=3, UGC_LIST_WILL_VOTE_LATER=4, UGC_LIST_FAVORITED=5, UGC_LIST_SUBSCRIBED=6, UGC_LIST_USED_OR_PLAYED=7, UGC_LIST_FOLLOWED=8,
			UGC_SORT_ORDER_CREATION_DESC=0, UGC_SORT_ORDER_CREATION_ASC=1, UGC_SORT_ORDER_TITLE_ASC=2, UGC_SORT_ORDER_LAST_UPDATE_DESC=3, UGC_SORT_ORDER_SUBSCRIPTION_DESC=4, UGC_SORT_ORDER_VOTE_SCORE_DESC=5, UGC_SORT_ORDER_FOR_MODERATION=6,
			UGC_FILE_VISIBLE_PUBLIC=0, UGC_FILE_VISIBLE_FRIENDS=1, UGC_FILE_VISIBLE_PRIVATE=2,
			UGC_ITEM_COMMUNITY=0, UGC_ITEM_MICROTRANSACTION=1, UGC_ITEM_COLLECTION=2, UGC_ITEM_ART=3, UGC_ITEM_VIDEO=4, UGC_ITEM_SCREENSHOT=5, UGC_ITEM_GAME=6, UGC_ITEM_SOFTWARE=7,
			UGC_ITEM_CONCEPT=8, UGC_ITEM_WEBGUIDE=9, UGC_ITEM_INTEGRATEDGUIDE=10, UGC_ITEM_MERCH=11, UGC_ITEM_CONTROLLERBINDING=12, UGC_ITEM_STEAMWORKSACCESSINVITE=13,
			UGC_ITEM_STEAMVIDEO=14, UGC_ITEM_GAMEMANAGEDITEM=15, UGC_ITEM_MAX=16,
			REMOTE_STORAGE_PLATFORM_NONE=0, REMOTE_STORAGE_PLATFORM_WINDOWS=(1<<0), REMOTE_STORAGE_PLATFORM_OSX=(1<<1), REMOTE_STORAGE_PLATFORM_PS3=(1<<2), 
			REMOTE_STORAGE_PLATFORM_LINUX=(1<<3), REMOTE_STORAGE_PLATFORM_RESERVED2=(1<<4), REMOTE_STORAGE_PLATFORM_ALL=0xffffffff,
			RESULT_OK=1, RESULT_FAIL=2, RESULT_NO_CONNECT=3, RESULT_INVALID_PASSWORD=5, RESULT_LOGGED_IN_ESLEWHERE=6, RESULT_INVALID_PROTOCAL=7, RESULT_INALID_PARAM=8, RESULT_FILE_NOT_FOUND=9, RESULT_BUSY=10, RESULT_INVALID_STATE=11, RESULT_INVALID_NAME=12,
			RESULT_INVALID_EMAIL=13, RESULT_DUPLICATE_NAME=14, RESULT_ACCESS_DENIED=15, RESULT_TIMEOUT=16, RESULT_BANNED=17, RESULT_ACCOUNT_NOT_FOUND=18, RESULT_INVALID_STEAM_ID=19, RESULT_SERVICE_UNAVAILABLE=20, RESULT_NOT_LOGGED_ON=21, RESULT_PENDING=22,
			RESULT_ENCRYPT_FAILURE=23, RESULT_INSUFFICIENT_PRIVILEGE=24, RESULT_LIMIT_EXCEEDED=25, RESULT_REVOKED=26, RESULT_EXPIRED=27, RESULT_ALREADY_REDEEMED=28, RESULT_DUPLICATE_REQUEST=29, RESULT_ALREADY_OWNED=30, RESULT_IP_NOT_FOUND=31, RESULT_PERSIST_FAILED=32,
			RESULT_LOCKING_FAILED=33, RESULT_LOGON_SESSION_REPLACED=34, RESULT_CONNECT_FAILED=35, RESULT_HANDSHAKE_FAILED=36, RESULT_IO_FAILURE=37, RESULT_REMOTE_DISCONNECT=38, RESULT_SHOPPING_CART_NOT_FOUND=39, RESULT_BLOCKED=40, RESULT_IGNORED=41, RESULT_NO_MATCH=42,
			RESULT_ACCOUNT_DISABLED=43, RESULT_SERVICE_READY_ONLY=44, RESULT_ACCOUNT_NOT_FEATURED=45, RESULT_ADMINISTRATOR_OK=46, RESULT_CONTENT_VERSION=47, RESULT_TRY_ANOTHER_CM=48, RESULT_PASSWORD_REQUIRED_TO_KICK=49, RESULT_ALREADY_LOGGED_ELSEWHERE=50,
			RESULT_SUSPENDED=51, RESULT_CANCELLED=52, RESULT_DATA_CORRUPTION=53, RESULT_DISK_FULL=54, RESULT_REMOTE_CALL_FAILED=55, RESULT_PASSWORD_UNSET=56, RESULT_EXTERNAL_ACCOUNT_UNLINKED=57, RESULT_PSN_TICKET_INVALID=58, RESULT_EXTERNAL_ACCOUNT_ALREADY_LINKED=59,
			RESULT_REMOTE_FILE_CONFLICT=60, RESULT_ILLEGAL_PASSWORD=61, RESULT_SAME_AS_PREVIOUS_VALUE=62, RESULT_ACCOUNT_LOGON_DENIED=63, RESULT_CANNOT_USE_OLD_PASSWORD=64, RESULT_INVALID_LOGIN_AUTH_CODE=65, RESULT_ACCOUNT_LOGON_DENIED_NO_MAIL=66, RESULT_HARDWARE_NOT_CAPABLE=67,
			RESULT_IP_INIT_ERROR=68, RESULT_PARENTAL_CONTROL_RESTRICTED=69, RESULT_FACEBOOK_QUERY_ERROR=70, RESULT_EXPIRED_LOGIN_AUTH_CODE=71, RESULT_IP_LOGIN_RESTRICTION_FAILED=72, RESULT_ACCOUNT_LOCKED_DOWN=73, RESULT_ACCOUNT_LOGON_DENIED_VERIFIED_EMAIL_REQUIRED=74,
			RESULT_NO_MATCHING_URL=75, RESULT_BAD_RESPONSE=76, RESULT_REQUIRED_PASSWORD_REENTRY=77, RESULT_VALUE_OUT_OF_RANGE=78, RESULT_UNEXPECTED_ERROR=79, RESULT_DISABLED=80, RESULT_INVALID_CEG_SUBMISSION=81, RESULT_RESTRICTED_DEVICE=82, RESULT_REGION_LOCKED=83,
			RESULT_RATE_LIMIT_EXCEEDED=84, RESULT_ACCOUNT_LOGIN_DENIED_NEED_TWO_FACTOR=85, RESULT_ITEM_DELETED=86, RESULT_ACCOUNT_LOGIN_DENIED_THROTTLE=87, RESULT_TWO_FACTOR_CODE_MISMATCH=88, RESULT_TWO_FACTOR_ACTIVATION_CODE_MISMATCH=89, RESULT_ACCOUNT_ASSOCIATED_TO_MULTIPLE_PARTNERS=90,
			RESULT_NOT_MODIFIED=91, RESULT_NO_MOBILE_DEVICE=92, RESULT_TIME_NOT_SYNCED=93, RESULT_SMS_CODE_FAILED=94, RESULT_ACCOUNT_LIMIT_EXCEEDED=95, RESULT_ACCOUNT_ACTIVITY_LIMIT_EXCEEDED=96, RESULT_PHONE_ACTIVITY_LIMIT_EXCEEDED=97, RESULT_REFUND_TO_WALLET=98,
			RESULT_EMAIL_SEND_FAILURE=99, RESULT_NOT_SETTLED=100, RESULT_NEED_CAPTCHA=101, RESULT_GSLT_DENIED=102, RESULT_GS_OWNER_DENIED=103,RESULT_INVALID_ITEM_TYPE=104, RESULT_IP_BANNED=105, RESULT_GSLT_EXPIRED=106, RESULT_INSUFFICIENT_FUNDS=107, RESULT_TOO_MANY_PENDING=108,
			CHAT_ROOM_SUCCESS=1, CHAT_ROOM_DOESNT_EXIST=2, CHAT_ROOM_NOT_ALLOWED=3, CHAT_ROOM_FULL=4, CHAT_ROOM_ERROR=5, CHAT_ROOM_BANNED=6, CHAT_ROOM_LIMITED=7, CHAT_ROOM_CLAN_DISABLED=8, CHAT_ROOM_COMMUNITY_BAN=9, CHAT_ROOM_MEMBER_BLOCKED_YOU=10, CHAT_ROOM_YOU_BLOCKED_MEMBER=11,
			GAMEID_TYPE_APP=0, GAMEID_TYPE_MOD=1, GAMEID_TYPE_SHORTCUT=2, GAMEID_TYPE_P2P=3,
			FAVORITE_FLAG_FAVORITE=0x01, FAVORITE_FLAG_HISTORY=0x02, FAVORITE_FLAG_NONE=0x00,
			CHAT_MEMBER_CHANGE_ENTERED=0x0001, CHAT_MEMBER_CHANGE_LEFT=0x0002, CHAT_MEMBER_CHANGE_DISCONNECTED=0x0004, CHAT_MEMBER_CHANGE_KICKED=0x0008, CHAT_MEMBER_CHANGE_BANNED=0x0010,
			FAILURE_FLUSHED_CALLBACK_QUEUE=0, FAILURE_PIPE_FAIL=1,
			GAMEPAD_INPUT_LINE_MODE_SINGLE=0, GAMEPAD_INPUT_LINE_MODE_MULTIPLE=1,
			GAMEPAD_INPUT_MODE_NORMAL=0, GAMEPAD_INPUT_MODE_PASSWORD=1,
			STEAM_API_CALL_FAILURE_NONE=-1, STEAM_API_CALL_FAILURE_STEAM_GONE=0, STEAM_API_CALL_FAILURE_NETWORK_FAILURE=1, STEAM_API_CALL_FAILURE_INVALID_HANDLE=2, STEAM_API_CALL_FAILURE_MISMATCHED_CALLBACK=3,
			LEADERBOARD_SORT_METHOD_NONE=0, LEADERBOARD_SORT_METHOD_ASC=1, LEADERBOARD_SORT_METHOD_DESC=2,
			LEADERBOARD_UPLOAD_METHOD_NONE=0, LEADERBOARD_UPLOAD_METHOD_KEEP_BEST=1, LEADERBOARD_UPLOAD_METHOD_FORCE_UPDATE=2,
			LEADERBOARD_DISPLAY_TYPE_NONE=0, LEADERBOARD_DISPLAY_TYPE_NUMERIC=1, LEADERBOARD_DISPLAY_TYPE_TIME_SECONDS=2, LEADERBOARD_DISPLAY_TYPE_TIME_MILLISECONDS=3,
			LEADERBOARD_DATA_REQUEST_GLOBAL=0, LEADERBOARD_DATA_REQUEST_GLOBAL_AROUND_USER=1, LEADERBOARD_DATA_REQUEST_FRIENDS=2, LEADERBOARD_DATA_REQUEST_USERS=3,
			DEVICE_FORM_FACTOR_UNKNOWN=0, DEVICE_FORM_FACTOR_PHONE=1, DEVICE_FORM_FACTOR_TABLET=2, DEVICE_FORM_FACTOR_COMPUTER=3, DEVICE_FORM_FACTOR_TV=4
		};
		static Steam* get_singleton();
		Steam();
		~Steam();

		CSteamID createSteamID(uint32_t steamID, int accountType=-1);

		// Main /////////////////////////////////
		bool restartAppIfNecessary(int value);
		Dictionary steamInit();
		bool isSteamRunning();

		// Apps /////////////////////////////////
		bool isSubscribed();
		bool isLowViolence();
		bool isCybercafe();
		bool isVACBanned();
		String getCurrentGameLanguage();
		String getAvailableGameLanguages();
		bool isSubscribedApp(int value);
		bool isDLCInstalled(int value);
		int getEarliestPurchaseUnixTime(int value);
		bool isSubscribedFromFreeWeekend();
		int getDLCCount();
		Array getDLCDataByIndex();
		void installDLC(int value);
		void uninstallDLC(int value);
		String getCurrentBetaName();
		bool markContentCorrupt(bool missingFilesOnly);
		Array getInstalledDepots(int appID);
		String getAppInstallDir(AppId_t appID);
		bool isAppInstalled(int value);
		uint64_t getAppOwner();
		String getLaunchQueryParam(const String& key);
		Dictionary getDLCDownloadProgress(int appID);
		int getAppBuildId();
		void getFileDetails(const String& filename);

		// Controller ///////////////////////////
		void activateActionSet(uint64_t controllerHandle, uint64_t actionSetHandle);
		uint64_t getActionSetHandle(const String& actionSetName);
		Dictionary getAnalogActionData(uint64_t controllerHandle, uint64_t analogActionHandle);
		uint64_t getAnalogActionHandle(const String& actionName);
		Array getAnalogActionOrigins(uint64_t controllerHandle, uint64_t actionSetHandle, uint64_t analogActionHandle);
		Array getConnectedControllers();
		uint64_t getControllerForGamepadIndex(int index);
		uint64_t getCurrentActionSet(uint64_t controllerHandle);
		uint64_t getInputTypeForHandle(uint64_t controllerHandle);
		Dictionary getDigitalActionData(uint64_t controllerHandle, uint64_t digitalActionHandle);
		uint64_t getDigitalActionHandle(const String& actionName);
		Array getDigitalActionOrigins(uint64_t controllerHandle, uint64_t actionSetHandle, uint64_t digitalActionHandle);
		int getGamepadIndexForController(uint64_t controllerHandle);
		Dictionary getMotionData(uint64_t controllerHandle);
		bool init();
		void runFrame();
		bool showBindingPanel(uint64_t controllerHandle);
		bool shutdown();
		void triggerVibration(uint64_t controllerHandle, uint16_t leftSpeed, uint16_t rightSpeed);

		// Friends //////////////////////////////
		String getPersonaName();
		void setPersonaName(const String& name);
		int getPersonaState();
		int getFriendCount();
		uint64_t getFriendByIndex(int friendNum, int friendFlags);
		int getFriendRelationship(uint64_t steamID);
		int getFriendPersonaState(uint64_t steamID);
		String getFriendPersonaName(uint64_t steamID);
		Dictionary getFriendGamePlayed(uint64_t steamID);
		String getFriendPersonaNameHistory(uint64_t steamID, int nameHistory);
		int getFriendSteamLevel(uint64_t steamID);
		String getPlayerNickname(uint64_t steamID);
		bool hasFriend(uint64_t steamID, int friendFlags);
		void downloadClanActivityCounts(uint64_t clanID, int clansToRequest);
		int getFriendCountFromSource(uint64_t clanID);
		uint64_t getFriendFromSourceByIndex(uint64_t sourceID, int friendNum);
		bool isUserInSource(uint64_t steamID, uint64_t sourceID);
		void setInGameVoiceSpeaking(uint64_t steamID, bool speaking);
		void activateGameOverlay(const String& type);
		void activateGameOverlayToUser(const String& type, uint64_t steamID);
		void activateGameOverlayToWebPage(const String& url);
		void activateGameOverlayToStore(int appID=0);
		void setPlayedWith(uint64_t steamID);
		void activateGameOverlayInviteDialog(uint64_t steamID);
		int getSmallFriendAvatar(uint64_t steamID);
		int getMediumFriendAvatar(uint64_t steamID);
		int getLargeFriendAvatar(uint64_t steamID);
		bool requestUserInformation(uint64_t steamID, bool requireNameOnly);
		void requestClanOfficerList(uint64_t clanID);
		uint64_t getClanOwner(uint64_t clanID);
		int getClanOfficerCount(uint64_t clanID);
		uint64_t getClanOfficerByIndex(uint64_t clanID, int officer);
		uint32 getUserRestrictions();
		bool setRichPresence(const String& key, const String& value);
		void clearRichPresence();
		String getFriendRichPresence(uint64_t friendID, const String& key);
		int getFriendRichPresenceKeyCount(uint64_t friendID);
		String getFriendRichPresenceKeyByIndex(uint64_t friendID, int key);
		void requestFriendRichPresence(uint64_t friendID);
		bool inviteUserToGame(uint64_t friendID, const String& connectString);
		void joinClanChatRoom(uint64_t clanID);
		bool leaveClanChatRoom(uint64_t clanID);
		int getClanChatMemberCount(uint64_t clanID);
		uint64_t getChatMemberByIndex(uint64_t clanID, int user);
		bool sendClanChatMessage(uint64_t chatID, const String& text);
		bool isClanChatAdmin(uint64_t chatID, uint64_t steamID);
		bool isClanChatWindowOpenInSteam(uint64_t chatID);
		bool openClanChatWindowInSteam(uint64_t chatID);
		bool closeClanChatWindowInSteam(uint64_t chatID);
		bool setListenForFriendsMessages(bool intercept);
		bool replyToFriendMessage(uint64_t steamID, const String& message);
		void getFollowerCount(uint64_t steamID);
		void isFollowing(uint64_t steamID);
		void enumerateFollowingList(uint32 startIndex);
		bool isClanPublic(uint64_t clanID);
		bool isClanOfficialGameGroup(uint64_t clanID);
		Array getRecentPlayers();
		void getPlayerAvatar(int size=AVATAR_MEDIUM, uint64_t steamID=0);
		Array getUserFriendsGroups();
		Array getUserSteamGroups();
		Array getUserSteamFriends();

		// Matchmaking //////////////////////////
		Array getFavoriteGames();
		int addFavoriteGame(uint32 ip, uint16 port, uint16 queryPort, uint32 flags, uint32 lastPlayed);
		bool removeFavoriteGame(AppId_t appID, uint32 ip, uint16 port, uint16 queryPort, uint32 flags);
		void requestLobbyList();
		void addRequestLobbyListStringFilter(const String& keyToMatch, const String& valueToMatch, int comparisonType);
		void addRequestLobbyListNumericalFilter(const String& keyToMatch, int valueToMatch, int comparisonType);
		void addRequestLobbyListNearValueFilter(const String& keyToMatch, int valueToBeCloseTo);
		void addRequestLobbyListFilterSlotsAvailable(int slotsAvailable);
		void addRequestLobbyListDistanceFilter(int distanceFilter);
		void addRequestLobbyListResultCountFilter(int maxResults);
		void createLobby(int lobbyType, int maxMembers);
		void joinLobby(uint64_t steamIDLobby);
		void leaveLobby(uint64_t steamIDLobby);
		bool inviteUserToLobby(uint64_t steamIDLobby, uint64_t steamIDInvitee);
		int getNumLobbyMembers(uint64_t steamIDLobby);
		uint64_t getLobbyMemberByIndex(uint64_t steamIDLobby, int member);
		String getLobbyData(uint64_t steamIDLobby, const String& key);
		bool setLobbyData(uint64_t steamIDLobby, const String& key, const String& value);
		Dictionary getLobbyDataByIndex(uint64_t steamIDLobby);
		bool deleteLobbyData(uint64_t steamIDLobby, const String& key);
		String getLobbyMemberData(uint64_t steamIDLobby, uint64_t steamIDUser, const String& key);
		void setLobbyMemberData(uint64_t steamIDLobby, const String& key, const String& value);
		bool sendLobbyChatMsg(uint64_t steamIDLobby, const String& messageBody);
		bool requestLobbyData(uint64_t steamIDLobby);
		void setLobbyGameServer(uint64_t steamIDLobby, const String& serverIP, uint16 serverPort, uint64_t steamIDGameServer);
		Dictionary getLobbyGameServer(uint64_t steamIDLobby);
		bool setLobbyMemberLimit(uint64_t steamIDLobby, int maxMembers);
		int getLobbyMemberLimit(uint64_t steamIDLobby);
		bool setLobbyType(uint64_t steamIDLobby, int eLobbyType);
		bool setLobbyJoinable(uint64_t steamIDLobby, bool joinable);
		uint64_t getLobbyOwner(uint64_t steamIDLobby);
		bool setLobbyOwner(uint64_t steamIDLobby, uint64_t steamIDNewOwner);
		bool setLinkedLobby(uint64_t steamIDLobby, uint64_t steamIDLobbyDependent);

		// Music ////////////////////////////////
		bool musicIsEnabled();
		bool musicIsPlaying();
		float musicGetVolume();
		void musicPause();
		void musicPlay();
		void musicPlayNext();
		void musicPlayPrev();
		void musicSetVolume(float value);

		// Networking ///////////////////////////
		bool acceptP2PSessionWithUser(uint64_t steamIDRemote);
		bool allowP2PPacketRelay(bool allow);
		bool closeP2PChannelWithUser(uint64_t steamIDRemote, int channel);
		bool closeP2PSessionWithUser(uint64_t steamIDRemote);
		Dictionary getP2PSessionState(uint64_t steamIDRemote);
		uint32_t getAvailableP2PPacketSize(int channel = 0);
		Dictionary readP2PPacket(uint32_t packet, int channel = 0);
		bool sendP2PPacket(uint64_t steamIDRemote, const PoolByteArray data, int eP2PSendType, int channel = 0);

		// Remote Play //////////////////////////
		uint32 getSessionCount();
		uint32 getSessionID(int index);
		uint64_t getSessionSteamID(uint32 sessionID);
		String getSessionClientName(uint32 sessionID);
		int getSessionClientFormFactor(uint32 sessionID);
		Dictionary getSessionClientResolution(uint32 sessionID);
	//	bool sendRemotePlayTogetherInvite(uint64_t friendID);

		// Remote Storage ///////////////////////
		bool fileWrite(const String& file, const PoolByteArray& data, int32_t dataSize);
		Dictionary fileRead(const String& file, int32_t dataToRead);
		bool fileForget(const String& file);
		bool fileDelete(const String& file);
		bool fileExists(const String& file);
		bool filePersisted(const String& file);
		int32_t getFileSize(const String& file);
		int64_t getFileTimestamp(const String& file);
		int32_t getFileCount();
		Dictionary getFileNameAndSize(int file);
		Dictionary getQuota();
		uint32_t getSyncPlatforms(const String& file);
		bool isCloudEnabledForAccount();
		bool isCloudEnabledForApp();
		void setCloudEnabledForApp(bool enabled);

		// Screenshots //////////////////////////
		uint32_t addScreenshotToLibrary(const String& filename, const String& thumbnailFilename, int width, int height);
		void hookScreenshots(bool hook);
		bool isScreenshotsHooked();
		bool setLocation(uint32_t screenshot, const String& location);
		void triggerScreenshot();
		uint32_t writeScreenshot(const PoolByteArray& RGB, int width, int height);

		// UGC //////////////////////////////////
		void addAppDependency(int publishedFileID, int appID);
		void addDependency(int publishedFileID, int childPublishedFileID);
		bool addExcludedTag(uint64_t queryHandle, const String& tagName);
		bool addItemKeyValueTag(uint64_t queryHandle, const String& key, const String& value);
		bool addItemPreviewFile(uint64_t queryHandle, const String& previewFile, int type);
		bool addItemPreviewVideo(uint64_t queryHandle, const String& videoID);
		void addItemToFavorite(int appID, int publishedFileID);
		bool addRequiredKeyValueTag(uint64_t queryHandle, const String& key, const String& value);
		bool addRequiredTag(uint64_t queryHandle, const String& tagName);
		bool initWorkshopForGameServer(int workshopDepotID);
		void createItem(AppId_t appID, int fileType);
		uint64_t createQueryAllUGCRequest(int queryType, int matchingType, int creatorID, int consumerID, uint32 page);
		uint64_t createQueryUGCDetailsRequest(Array publishedFileID);
//		uint64_t createQueryUserUGCRequest(int accountID, int listType, int matchingUGCType, int sortOrder, int creatorID, int consumerID, uint32 page);
		void deleteItem(int publishedFileID);
		bool downloadItem(int publishedFileID, bool highPriority);
		Dictionary getItemDownloadInfo(int fileID);
		Dictionary getItemInstallInfo(int publishedFileID);
		int getItemState(int publishedFileID);
		Dictionary getItemUpdateProgress(uint64_t updateHandle);
		uint32 getNumSubscribedItems();
		Dictionary getQueryUGCAdditionalPreview(uint64_t queryHandle, uint32 index, uint32 previewIndex);
		Dictionary getQueryUGCChildren(uint64_t queryHandle, uint32 index);
		Dictionary getQueryUGCKeyValueTag(uint64_t queryHandle, uint32 index, uint32 keyValueTagIndex);
		String getQueryUGCMetadata(uint64_t queryHandle, uint32 index);
		uint32 getQueryUGCNumAdditionalPreviews(uint64_t queryHandle, uint32 index);
		uint32 getQueryUGCNumKeyValueTags(uint64_t queryHandle, uint32 index);
		String getQueryUGCPreviewURL(uint64_t queryHandle, uint32 index);
		Dictionary getQueryUGCResult(uint64_t queryHandle, uint32 index);
		Dictionary getQueryUGCStatistic(uint64_t queryHandle, uint32 index, int statType);
		Array getSubscribedItems();
		void getUserItemVote(int publishedFileID);
		bool releaseQueryUGCRequest(uint64_t queryHandle);
		void removeAppDependency(int publishedFileID, int appID);
		void removeDependency(int publishedFileID, int childPublishedFileID);
		void removeItemFromFavorites(int appID, int publishedFileID);
		bool removeItemKeyValueTags(uint64_t updateHandle, const String& key);
		bool removeItemPreview(uint64_t updateHandle, uint32 index);
		void sendQueryUGCRequest(uint64_t updateHandle);
		bool setAllowCachedResponse(uint64_t updateHandle, uint32 maxAgeSeconds);
		bool setCloudFileNameFilter(uint64_t updateHandle, const String& matchCloudFilename);
		bool setItemContent(uint64_t updateHandle, const String& contentFolder);
		bool setItemDescription(uint64_t updateHandle, const String& description);
		bool setItemMetadata(uint64_t updateHandle, const String& metadata);
		bool setItemPreview(uint64_t updateHandle, const String& previewFile);
//		bool setItemTags(uint64_t updateHandle, Array tagArray);
		bool setItemTitle(uint64_t updateHandle, const String& title);
		bool setItemUpdateLanguage(uint64_t updateHandle, const String& language);
		bool setItemVisibility(uint64_t updateHandle, int visibility);
		bool setLanguage(uint64_t queryHandle, const String& language);
		bool setMatchAnyTag(uint64_t queryHandle, bool matchAnyTag);
		bool setRankedByTrendDays(uint64_t queryHandle, uint32 days);
		bool setReturnAdditionalPreviews(uint64_t queryHandle, bool returnAdditionalPreviews);
		bool setReturnChildren(uint64_t queryHandle, bool returnChildren);
		bool setReturnKeyValueTags(uint64_t queryHandle, bool returnKeyValueTags);
		bool setReturnLongDescription(uint64_t queryHandle, bool returnLongDescription);
		bool setReturnMetadata(uint64_t queryHandle, bool returnMetadata);
		bool setReturnOnlyIDs(uint64_t queryHandle, bool returnOnlyIDs);
		bool setReturnPlaytimeStats(uint64_t queryHandle, uint32 days);
		bool setReturnTotalOnly(uint64_t queryHandle, bool returnTotalOnly);
		bool setSearchText(uint64_t queryHandle, const String& searchText);
		void setUserItemVote(int publishedFileID, bool voteUp);
		uint64_t startItemUpdate(int appID, int fileId);
		void startPlaytimeTracking(Array publishedFileIDs);
		void stopPlaytimeTracking(Array publishedFileIDs);
		void stopPlaytimeTrackingForAllItems();
		void getAppDependencies(int publishedFileID);
		void submitItemUpdate(uint64_t updateHandle, const String& changeNote);
		void subscribeItem(int publishedFileID);
		void suspendDownloads(bool suspend);
		void unsubscribeItem(int publishedFileID);
		bool updateItemPreviewFile(uint64_t updateHandle, uint32 index, const String& previewFile);
		bool updateItemPreviewVideo(uint64_t updateHandle, uint32 index, const String& videoID);

		// Users ////////////////////////////////
		uint32_t getAuthSessionTicket();
		void cancelAuthTicket(uint32_t authTicket);
		int beginAuthSession(uint32_t authTicket, uint64_t steamID);
		void endAuthSession(uint64_t steamID);
		uint64_t getSteamID();
		bool loggedOn();
		int getPlayerSteamLevel();
		String getUserDataFolder();
		void advertiseGame(const String& serverIP, int port);
		int getGameBadgeLevel(int series, bool foil);

		// User Stats ///////////////////////////
		void attachLeaderboardUGC();
		bool clearAchievement(const String& name);
		void downloadLeaderboardEntries(int start, int end, int type=GLOBAL);
		void downloadLeaderboardEntriesForUsers(Array usersID);
		void findLeaderboard(const String& name);
		void findOrCreateLeaderboard(const String& name, int sortMethod, int displayType);
		Dictionary getAchievement(const String& name);
		Dictionary getAchievementAchievedPercent(const String& name);
		Dictionary getAchievementAndUnlockTime(const String& name);
		String getAchievementDisplayAttribute(const String& name, const String& key);
		int getAchievementIcon(const String& name);
		String getAchievementName(uint32_t achievement);
		void getDownloadedLeaderboardEntry(uint64_t handle, int entryCount);
		uint64 getGlobalStatInt(const String& name);
		double getGlobalStatFloat(const String& name);
		uint64 getGlobalStatIntHistory(const String& name);
		double getGlobalStatFloatHistory(const String& name);
		int getLeaderboardDisplayType();
		int getLeaderboardEntryCount();
		String getLeaderboardName();
		int getLeaderboardSortMethod();
		Array getMostAchievedAchievementInfo();
		uint32_t getNumAchievements();
		void getNumberOfCurrentPlayers();
		float getStatFloat(const String& name);
		int getStatInt(const String& name);
		Dictionary getUserAchievement(uint64_t steamID, const String& name);
		Dictionary getUserAchievementAndUnlockTime(uint64_t steamID, const String& name);
		float getUserStatFloat(uint64_t steamID, const String& name);
		int getUserStatInt(uint64_t steamID, const String& name);
		bool indicateAchievementProgress(const String& name, int currentProgress, int maxProgress);
		bool requestCurrentStats();
		void requestGlobalAchievementPercentages();
		void requestGlobalStats(int historyDays);
		void requestUserStats(uint64_t steamID);
		bool resetAllStats(bool achievementsToo=true);
		bool setAchievement(const String& name);
		bool setStatFloat(const String& name, float value);
		bool setStatInt(const String& name, int value);
		bool storeStats();
		bool updateAvgRateStat(const String& name, float thisSession, double sessionLength);
		void uploadLeaderboardScore(int score, bool keepBest=false, PoolIntArray details=PoolIntArray());
		uint64_t getLeaderboardHandle();
		Array getLeaderboardEntries();
		void setLeaderboardDetailsMax(int detailsMax);

		// Utils ////////////////////////////////
		bool overlayNeedsPresent();
		int getAppID();
		int getCurrentBatteryPower();
		Dictionary getImageRGBA(int iImage);
		Dictionary getImageSize(int iImage);
		uint32 getIPCCallCount();
		String getIPCountry();
		int getSecondsSinceAppActive();
		int getSecondsSinceComputerActive();
		int getServerRealTime();
		String getSteamUILanguage();
		bool isOverlayEnabled();
		bool isSteamInBigPictureMode();
		bool isSteamRunningInVR();
		bool isVRHeadsetStreamingEnabled();
		void setOverlayNotificationInset(int horizontal, int vertical);
		void setOverlayNotificationPosition(int pos);
		void setVRHeadsetStreamingEnabled(bool enabled);
		bool showGamepadTextInput(int inputMode, int lineInputMode, const String& description, uint32 maxText, const String& presetText);
		void startVRDashboard();

	protected:
		static void _bind_methods();
		static Steam* singleton;

	private:
		// Main
		bool isInitSuccess;

		// Apps
		uint64 currentAppID;
		
		// Matchmaking
		CSteamID clanActivity;

		// Leaderboards
		SteamLeaderboard_t leaderboardHandle;
		Array leaderboardEntries;
		int leaderboardDetailsMax;

		// Remote Play
		uint32 sessionID;

		// User stats
		int numAchievements;
		bool statsInitialized;
		uint64 ugcHandle;

		/////////////////////////////////////////
		// STRUCTS //////////////////////////////
		/////////////////////////////////////////
		//
		// Authentication ///////////////////////
		struct TicketData {
			uint32_t id;
			uint32_t *buffer;
			uint32_t size;
		};
		Vector<TicketData> tickets;

		// Friend session state info ////////////
		struct FriendSessionStateInfo {
			uint32 onlineSessionInstance;
			uint8 publishedToFriendsSessionInstance;
		};
		Vector<FriendSessionStateInfo> sessionInfo;

		// Achievement data /////////////////////
		struct AchievementData {
			int achievementID;
			const char achievement;
			char name[128];
			char description[256];
			bool achieved;
			int icon;
		};
		Vector<AchievementData> achievementData;

		// Leaderboard entry ////////////////////
		struct LeaderboardEntry {
			uint64_t steamID;
			int32 globalRank;
			int32 score;
			int32 details;
			uint64 ugcHandle; 
		};
		Vector<LeaderboardEntry> leaderboardEntry;

		// UGC item details /////////////////////
		struct UGCDetails {
			int publishedFileID;
			int result;
			int fileType;
			int creatorAppID;
			int consumerAppID;
			char title[128];
			char description[256];
			uint64_t steamIDOwner;
			uint32 timeCreated;
			uint32 timeUpdated;
			uint32 timeAddedToList;
			int visibility;
			bool banned;
			bool acceptedForUse;
			bool tagsTruncated;
			char tags[256];
			int file;
			int previewFile;
			char filename[128];
			int32 fileSize;
			int32 previewFileSize;
			char url[256];
			uint32 votesUp;
			uint32 votesDown;
			float score;
			uint32 numChildren;
		};
		Vector<UGCDetails> ugcDetails;
		/////////////////////////////////////////
		// STEAM CALLBACKS //////////////////////
		/////////////////////////////////////////
		//
		// Apps callbacks ///////////////////////
		STEAM_CALLBACK(Steam, _dlc_installed, DlcInstalled_t);
		STEAM_CALLBACK(Steam, _file_details_result, FileDetailsResult_t);
		STEAM_CALLBACK(Steam, _new_launch_url_parameters, NewUrlLaunchParameters_t);

		// Friends callbacks ////////////////////
		STEAM_CALLBACK(Steam, _avatar_loaded, AvatarImageLoaded_t);
		CCallResult<Steam, ClanOfficerListResponse_t> callResultClanOfficerList;
		void _request_clan_officer_list(ClanOfficerListResponse_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _clan_activity_downloaded, DownloadClanActivityCountsResult_t);
		STEAM_CALLBACK(Steam, _friend_rich_presence_update, FriendRichPresenceUpdate_t);
		CCallResult<Steam, FriendsEnumerateFollowingList_t> callResultEnumerateFollowingList;
		void _enumerate_following_list(FriendsEnumerateFollowingList_t *callData, bool bIOFailure);
		CCallResult<Steam, FriendsGetFollowerCount_t> callResultFollowerCount;
		void _get_follower_count(FriendsGetFollowerCount_t *callData, bool bIOFailure);
		CCallResult<Steam, FriendsIsFollowing_t> callResultIsFollowing;
		void _is_following(FriendsIsFollowing_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _connected_chat_join, GameConnectedChatJoin_t);
		STEAM_CALLBACK(Steam, _connected_chat_leave, GameConnectedChatLeave_t);
		STEAM_CALLBACK(Steam, _connected_clan_chat_message, GameConnectedClanChatMsg_t);
		STEAM_CALLBACK(Steam, _connected_friend_chat_message, GameConnectedFriendChatMsg_t);
		STEAM_CALLBACK(Steam, _join_requested, GameLobbyJoinRequested_t);
		STEAM_CALLBACK(Steam, _overlay_toggled, GameOverlayActivated_t);
		STEAM_CALLBACK(Steam, _join_game_requested, GameRichPresenceJoinRequested_t);
		STEAM_CALLBACK(Steam, _change_server_requested, GameServerChangeRequested_t);
		STEAM_CALLBACK(Steam, _join_clan_chat_complete, JoinClanChatRoomCompletionResult_t);
		STEAM_CALLBACK(Steam, _persona_state_change, PersonaStateChange_t);
		STEAM_CALLBACK(Steam, _name_changed, SetPersonaNameResponse_t);

		// Matchmaking callbacks ////////////////
		STEAM_CALLBACK(Steam, _favorites_list_accounts_updated, FavoritesListAccountsUpdated_t);
		STEAM_CALLBACK(Steam, _favorites_list_changed, FavoritesListChanged_t);
		STEAM_CALLBACK(Steam, _lobby_message, LobbyChatMsg_t);
		STEAM_CALLBACK(Steam, _lobby_chat_update, LobbyChatUpdate_t);
		CCallResult<Steam, LobbyCreated_t> callResultCreateLobby;
		void _lobby_created(LobbyCreated_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _lobby_data_update, LobbyDataUpdate_t);
		STEAM_CALLBACK(Steam, _lobby_joined, LobbyEnter_t);
		STEAM_CALLBACK(Steam, _lobby_game_created, LobbyGameCreated_t);
		STEAM_CALLBACK(Steam, _lobby_invite, LobbyInvite_t);
		CCallResult<Steam, LobbyMatchList_t> callResultLobbyList;
		void _lobby_match_list(LobbyMatchList_t *callData, bool bIOFailure);

		// Networking callbacks /////////////////
		STEAM_CALLBACK(Steam, _p2p_session_connect_fail, P2PSessionConnectFail_t);
		STEAM_CALLBACK(Steam, _p2p_session_request, P2PSessionRequest_t);

		// Remote Play callbacks ////////////////
		STEAM_CALLBACK(Steam, _remote_play_session_connected, SteamRemotePlaySessionConnected_t);
		STEAM_CALLBACK(Steam, _remote_play_session_disconnected, SteamRemotePlaySessionDisconnected_t);

		// Remote Storage callbacks /////////////
		CCallResult<Steam, RemoteStorageUnsubscribePublishedFileResult_t> callResultUnsubscribeItem;
		void _unsubscribe_item(RemoteStorageUnsubscribePublishedFileResult_t *callData, bool bIOFailure);
		CCallResult<Steam, RemoteStorageSubscribePublishedFileResult_t> callResultSubscribeItem;
		void _subscribe_item(RemoteStorageSubscribePublishedFileResult_t *callData, bool bIOFailure);

		// Screenshot callbacks /////////////////
		STEAM_CALLBACK(Steam, _screenshot_ready, ScreenshotReady_t);
		STEAM_CALLBACK(Steam, _screenshot_requested, ScreenshotRequested_t);

		// UGC callbacks ////////////////////////
		CCallResult<Steam, AddAppDependencyResult_t> callResultAddAppDependency;
		void _add_app_dependency_result(AddAppDependencyResult_t *callData, bool bIOFailure);
		CCallResult<Steam, AddUGCDependencyResult_t> callResultAddUGCDependency;
		void _add_ugc_dependency_result(AddUGCDependencyResult_t *callData, bool bIOFailure);
		CCallResult<Steam, CreateItemResult_t> callResultItemCreate;
		void _item_created(CreateItemResult_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _item_downloaded, DownloadItemResult_t);
		CCallResult<Steam, GetAppDependenciesResult_t> callResultGetAppDependencies;
		void _get_app_dependencies_result(GetAppDependenciesResult_t *callData, bool bIOFailure);
		CCallResult<Steam, DeleteItemResult_t> callResultDeleteItem;
		void _item_deleted(DeleteItemResult_t *callData, bool bIOFailure);
		CCallResult<Steam, GetUserItemVoteResult_t> callResultGetUserItemVote;
		void _get_item_vote_result(GetUserItemVoteResult_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _item_installed, ItemInstalled_t);
		CCallResult<Steam, RemoveAppDependencyResult_t> callResultRemoveAppDependency;
		void _remove_app_dependency_result(RemoveAppDependencyResult_t *callData, bool bIOFailure);
		CCallResult<Steam, RemoveUGCDependencyResult_t> callResultRemoveUGCDependency;
		void _remove_ugc_dependency_result(RemoveUGCDependencyResult_t *callData, bool bIOFailure);
		CCallResult<Steam, SetUserItemVoteResult_t> callResultSetUserItemVote;
		void _set_user_item_vote(SetUserItemVoteResult_t *callData, bool bIOFailure);
		CCallResult<Steam, StartPlaytimeTrackingResult_t> callResultStartPlaytimeTracking;
		void _start_playtime_tracking(StartPlaytimeTrackingResult_t *callData, bool bIOFailure);
		CCallResult<Steam, SteamUGCQueryCompleted_t> callResultUGCQueryCompleted;
		void _ugc_query_completed(SteamUGCQueryCompleted_t *callData, bool bIOFailure);
		CCallResult<Steam, StopPlaytimeTrackingResult_t> callResultStopPlaytimeTracking;
		void _stop_playtime_tracking(StopPlaytimeTrackingResult_t *callData, bool bIOFailure);
		CCallResult<Steam, SubmitItemUpdateResult_t> callResultItemUpdate;
		void _item_updated(SubmitItemUpdateResult_t *callData, bool bIOFailure);
		CCallResult<Steam, UserFavoriteItemsListChanged_t> callResultFavoriteItemListChanged;
		void _user_favorite_items_list_changed(UserFavoriteItemsListChanged_t *callData, bool bIOFailure);

		// User callbacks ///////////////////////
		STEAM_CALLBACK(Steam, _client_game_server_deny, ClientGameServerDeny_t);
		STEAM_CALLBACK(Steam, _encrypted_app_ticket_response, EncryptedAppTicketResponse_t);
		STEAM_CALLBACK(Steam, _game_web_callback, GameWebCallback_t);
		STEAM_CALLBACK(Steam, _get_auth_session_ticket_response, GetAuthSessionTicketResponse_t);
		STEAM_CALLBACK(Steam, _ipc_failure, IPCFailure_t);
		STEAM_CALLBACK(Steam, _licenses_updated, LicensesUpdated_t);
		STEAM_CALLBACK(Steam, _microstransaction_auth_response, MicroTxnAuthorizationResponse_t);
		CCallResult<Steam, SteamServerConnectFailure_t> callResultSteamServerConnectFailure;
		void _steam_server_connect_failed(SteamServerConnectFailure_t *callData);
		STEAM_CALLBACK(Steam, _steam_server_connected, SteamServersConnected_t);
		STEAM_CALLBACK(Steam, _steam_server_disconnected, SteamServersDisconnected_t);
		STEAM_CALLBACK(Steam, _store_auth_url_response, StoreAuthURLResponse_t);
		STEAM_CALLBACK(Steam, _validate_auth_ticket_response, ValidateAuthTicketResponse_t);

		// User stat callbacks //////////////////
		CCallResult<Steam, GlobalAchievementPercentagesReady_t> callResultGlobalAchievementPercentagesReady;
		void _global_achievement_percentages_ready(GlobalAchievementPercentagesReady_t *callData, bool bIOFailure);
		CCallResult<Steam, GlobalStatsReceived_t> callResultGetGlobalStatsReceived;
		void _global_stats_received(GlobalStatsReceived_t *callData, bool bIOFailure);
		CCallResult<Steam, LeaderboardFindResult_t> callResultFindLeaderboard;
		void _leaderboard_find_result(LeaderboardFindResult_t *callData, bool bIOFailure);
		CCallResult<Steam, LeaderboardScoresDownloaded_t> callResultEntries;
		void _leaderboard_scores_downloaded(LeaderboardScoresDownloaded_t *callData, bool bIOFailure);
		CCallResult<Steam, LeaderboardScoreUploaded_t> callResultUploadScore;
		void _leaderboard_score_uploaded(LeaderboardScoreUploaded_t *callData, bool bIOFailure);
		CCallResult<Steam, LeaderboardUGCSet_t> callResultLeaderboardUGCSet;
		void _leaderboard_ugc_set(LeaderboardUGCSet_t *callData, bool bIOFailure);
		CCallResult<Steam, NumberOfCurrentPlayers_t> callResultNumberOfCurrentPlayers;
		void _number_of_current_players(NumberOfCurrentPlayers_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _user_achievement_icon_fetched, UserAchievementIconFetched_t);
		STEAM_CALLBACK(Steam, _user_achievement_stored, UserAchievementStored_t);
		CCallResult<Steam, UserStatsReceived_t> callResultUserStatsReceived;
		void _user_stats_received_callresult(UserStatsReceived_t *callData, bool bIOFailure);
		STEAM_CALLBACK(Steam, _user_stats_received_callback, UserStatsReceived_t);
		STEAM_CALLBACK(Steam, _user_stats_stored, UserStatsStored_t);
		STEAM_CALLBACK(Steam, _user_stats_unloaded, UserStatsUnloaded_t);

		// Utility callbacks ////////////////////
		CCallResult<Steam, CheckFileSignature_t> callResultCheckFileSignature;
		void _check_file_signature(CheckFileSignature_t *callData);
		STEAM_CALLBACK(Steam, _gamepad_text_input_dismissed, GamepadTextInputDismissed_t);
		STEAM_CALLBACK(Steam, _ip_country, IPCountry_t);
		STEAM_CALLBACK(Steam, _low_power, LowBatteryPower_t);
		STEAM_CALLBACK(Steam, _steam_api_call_completed, SteamAPICallCompleted_t);
		STEAM_CALLBACK(Steam, _steam_shutdown, SteamShutdown_t);

		// Run the Steamworks API callbacks /////
		void run_callbacks(){
			SteamAPI_RunCallbacks();
		}
};
#endif // GODOTSTEAM_H