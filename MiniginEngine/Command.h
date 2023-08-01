#pragma once
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		virtual void Update() = 0;
	};
}

