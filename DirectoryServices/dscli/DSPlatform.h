#import <Foundation/Foundation.h>

@protocol DSPlatform <NSObject>

@required

// Platform identification
- (NSString *)platformName;
- (BOOL)isAvailable;

// Directory Services daemons (gdomap + dshelper): enable them at boot and
// start them if they are not already running.  Idempotent, so it is safe to
// call on every "dscli init".
- (BOOL)enableDirectoryServices;

// Server (promote) operations
- (BOOL)configureNFSExports;
- (BOOL)enableNFSServer;
- (BOOL)startNFSServer;
- (BOOL)restartDSHelper;

// Server (demote) operations
- (BOOL)removeNFSExports;
- (BOOL)stopNFSServer;
- (BOOL)unregisterService;

// Client (join) operations
- (BOOL)enableNFSClient;
- (BOOL)startNFSClient;
- (BOOL)createNetworkMount:(NSString *)server;
- (BOOL)addFstabEntry:(NSString *)server;
- (BOOL)mountNetwork;

// Discovery
- (NSString *)discoverDirectoryServer;

// Client (leave) operations
- (BOOL)unmountNetwork;
- (BOOL)removeFstabEntry;

@optional
// Server: list currently-connected NFS client IPs (live, not historical).
// Returns nil if the platform has no implementation yet; caller may fall back.
- (NSArray<NSString *> *)connectedClients;

@end

// Get the appropriate platform implementation for the current system
id<DSPlatform> DSPlatformCreate(void);
