#pragma once

/// <summary>
/// @author Joshua Boyce Hyland
/// </summary>

/// <summary>
/// Subscriber interface so user can be notified of events during path finidng
/// </summary>
class AgentUser
{
	public:
		
		virtual void reachedTarget() = 0;
};

