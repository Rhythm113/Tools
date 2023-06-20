#Date: 2023-06-20 09:41 PM
#Simple IOCTL Analyzer helper by @Rhythm113

import idaapi
import idc
import idautils



def find_ioctl_functions():
    ioctl_functions = []
    for func_ea in Functions():
        func_name = GetFunctionName(func_ea)
        if "ioctl" in func_name:
            ioctl_functions.append(func_ea)

    return ioctl_functions

def analyze_ioctl_function(func_ea):
    print("Analyzing function at address: 0x{:X}".format(func_ea))
    case_map = {}  # Dictionary to store case connections
    root_case = None

    for (startea, endea) in idautils.Chunks(func_ea):
        for head in idautils.Heads(startea, endea):
            if idc.isCode(GetFlags(head)):
                insn = idc.GetDisasm(head)
                if "case" in insn:
                    case_num = idc.GetOperandValue(head, 0)
                    case_map[case_num] = []  # Initialize an empty list for case connections

                    if not root_case:
                        root_case = case_num  # Set the first case encountered as the root case

                elif "j" in insn and insn.startswith("jumptable"):
                    targets = idautils.CodeRefsFrom(head, 1)
                    for target in targets:
                        target_insn = idc.GetDisasm(target)
                        if "case" in target_insn:
                            target_case_num = idc.GetOperandValue(target, 0)
                            case_map[case_num].append(target_case_num)  # Add case connection

    return root_case, case_map

def find_connected_classes():
    connected_classes = []
    for class_ea in idautils.ClassInstances():
        class_name = idc.GetClassName(class_ea)
        lib_name = idc.GetLongPrm(idc.INF_SHORT_LPSNAME)
        if lib_name not in class_name:
            connected_classes.append((class_name, class_ea))

    return connected_classes

class FindIoctlPlugin(idaapi.plugin_t):
    flags = idaapi.PLUGIN_UNL
    comment = "Find IOCTL functions and analyze cases"
    help = "This plugin searches for functions containing 'ioctl' in their names, analyzes the case connections, and identifies classes connected to other libraries."
    wanted_name = "Find IOCTL"
    wanted_hotkey = "Alt-F9"
    author = "Rhythm113"

    def init(self):
        return idaapi.PLUGIN_OK

    def run(self, arg):
        ioctl_functions = find_ioctl_functions()
        if len(ioctl_functions) == 0:
            print("No functions containing 'ioctl' found.")
        else:
            print("Found {} functions containing 'ioctl':".format(len(ioctl_functions)))
            for func_ea in ioctl_functions:
                root_case, case_map = analyze_ioctl_function(func_ea)
                print("Root case number: {}".format(root_case))
                for case_num, connections in case_map.items():
                    print("Case {}: connected to cases {}".format(case_num, connections))

            connected_classes = find_connected_classes()
            if len(connected_classes) == 0:
                print("No classes connected to other libraries found.")
            else:
                print("Found {} classes connected to other libraries:".format(len(connected_classes)))
                for class_name, class_ea in connected_classes:
                    print("Class: {} at address 0x{:X}".format(class_name, class_ea))

    def term(self):
        pass

def PLUGIN_ENTRY():
    return FindIoctlPlugin()
