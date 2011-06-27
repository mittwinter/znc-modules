#include <main.h>
#include <Modules.h>

#include <User.h>
#include <Client.h>
#include <Chan.h>

class CQueryDemux : public CModule {
	public:
		MODCONSTRUCTOR( CQueryDemux ) {}
		virtual ~CQueryDemux() {}

		virtual EModRet OnUserMsg( CString &target, CString &message ) {
			CUser *user = GetUser();
			if( user != NULL ) {
				bool targetIsChannel = false;
				for( std::vector< CChan * >::const_iterator it = user->GetChans().begin(); it != user->GetChans().end(); it++ ) {
					if( target == (*it)->GetName() ) {
						targetIsChannel = true;
						break;
					}
				}
				if( !targetIsChannel ) {
					std::vector< CClient * > &clients = user->GetClients();
					for( std::vector< CClient * >::iterator it = clients.begin(); it != clients.end(); it++ ) {
						if( *it != m_pClient ) {
							(*it)->PutClient( ":" + target + " PRIVMSG " + user->GetCurNick() + " :<" + user->GetCurNick() + "> " + message );
						}
					}
				}
			}
			return CONTINUE;
		}
};

MODULEDEFS( CQueryDemux, "[description]" )
