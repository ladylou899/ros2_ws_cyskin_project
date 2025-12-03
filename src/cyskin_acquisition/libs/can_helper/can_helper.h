#ifndef CAN_HELPER_H
#define CAN_HELPER_H

#include <cynetwork.h>
#include <iostream>
#include <chrono>
#include <set>
#include <cstdio>


static CyCommCan *get_comm_can(int argc, char **argv, CyBusParamsCan can, std::set<unsigned int> &buses,
		const char *additional_help, CyCommPhase phase, bool no_change_phase = false)
{
	CyCommCan *can_dev = NULL;
#if defined(CY_SUPPORT_PCAN) && defined(CY_SUPPORT_ESDCAN)
	bool is_pcan = false;
	bool is_esdcan = false;
#endif
	bool is_st = false;
	bool is_ext = false;
	for (int i = 1; i < argc; ++i)
	{
		if (std::strcmp(argv[i], "--help") == 0)
		{
			std::cout << "Usage: " << argv[0] << " [--pcan|--esdcan] [--st|--ext] [--btldr|--app] [--bus N[-M]]* "
				<< (additional_help?additional_help:"") << std::endl;
			return NULL;
		}
		else if (std::strcmp(argv[i], "--pcan") == 0)
		{
#if defined(CY_SUPPORT_PCAN) && defined(CY_SUPPORT_ESDCAN)
			is_pcan = true;
#elif !defined(CY_SUPPORT_PCAN)
			//std::cout << "No support for PCAN" << std::endl;
			//return NULL;
#endif
		}
		else if (std::strcmp(argv[i], "--esdcan") == 0)
		{
#if defined(CY_SUPPORT_PCAN) && defined(CY_SUPPORT_ESDCAN)
			is_esdcan = true;
#elif !defined(CY_SUPPORT_ESDCAN)
			//std::cout << "No support for ESD CAN" << std::endl;
			//return NULL;
#endif
		}
		else if (std::strcmp(argv[i], "--st") == 0)
			is_st = true;
		else if (std::strcmp(argv[i], "--ext") == 0)
			is_ext = true;
		else if (std::strcmp(argv[i], "--btldr") == 0)
		{
			if (!no_change_phase)
				phase = CY_PHASE_BOOTLOAD;
		}
		else if (std::strcmp(argv[i], "--app") == 0)
		{
			if (!no_change_phase)
				phase = CY_PHASE_APPLICATION;
		}
		else if (std::strcmp(argv[i], "--bus") == 0)
		{
			if (i + 1 >= argc)
			{
				std::cout << "--bus needs to be followed by a bus number" << std::endl;
				continue;
			}
			++i;
			int b, c;

			/* try to see if range is given */
			if (std::sscanf(argv[i], "%d-%d", &b, &c) == 2)
			{
				if (b < 0 || c < 0)
				{
					std::cout << "--bus needs to be followed by a non-negative bus number or a range" << std::endl;
					continue;
				}
				else
					for (int j = b; j <= c; ++j)
						buses.insert(j);
			}
			else
			{
				if (std::sscanf(argv[i], "%d", &b) != 1 || b < 0)
				{
					std::cout << "--bus needs to be followed by a non-negative bus number or a range" << std::endl;
					continue;
				}
				buses.insert(b);
			}
		}
		else if (argv[i][0] == '-' && (additional_help == NULL || additional_help[0] == '\0'))
			std::cout << "Unknown option " << argv[i] << std::endl;
	}
	if (is_st && is_ext)
		std::cout << "Both standard and extended modes are not supported together." << std::endl
			<< "Defaulting to standard mode" << std::endl;
	can.msgtype = CY_CAN_MSG_ST;
	if (!is_st && is_ext)
		can.msgtype = CY_CAN_MSG_EXT;
#if defined(CY_SUPPORT_PCAN) && defined(CY_SUPPORT_ESDCAN)
	if (is_pcan)
		can_dev = new CyCommPCan(phase);
	else if (is_esdcan)
		can_dev = new CyCommEsdCan(phase);
#elif defined(CY_SUPPORT_PCAN)
	can_dev = new CyCommPCan(phase);
#elif defined(CY_SUPPORT_ESDCAN)
	can_dev = new CyCommEsdCan(phase);
#endif
	if (can_dev == NULL)
		std::cout << "No CAN support" << std::endl;
	if (buses.empty())
		buses.insert(0);

	return can_dev;
}

int switch_everyone_to_application(int argc, char **argv, CyBusParamsCan can, std::set<unsigned int >&buses, const char *additional_help)
{
	argv[argc] = (char *)"--ext";
	CyCommCan *can_dev = get_comm_can(argc + 1, argv, can, buses, additional_help, CY_PHASE_BOOTLOAD, true);
	if (can_dev == NULL)
		return -1;

	CyNetwork net(can_dev);
	for (auto i: buses)
		net.get_comm()->add_bus(i);

	CyTransmitProgress p;
	net.get_network_structure();
	net.get_utils()->send_bootloader_exit(CyBroadcast, &p);
	p.wait_transmit(CY_1_SEC);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	return 0;
}

#endif
