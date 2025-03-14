class Command:
    def __init__(self, fn, *args):
        self._fn = fn
        self._fn_params = args

    def execute(self):
        self._fn(*self._fn_params)

    def __str__(self):
        return "Function:" + str(self._fn)+"|| Parameters: "+ str(self._fn_params)


class Operation:
    def __init__(self, undo_action: Command, redo_action: Command):
        self.__undo_action = undo_action
        self.__redo_action = redo_action

    def undo(self):
        self.__undo_action.execute()

    def redo(self):
        self.__redo_action.execute()

    def __str__(self):
        return "Operation:" + str(self.__undo_action)+ " & "+str(self.__redo_action)


# class CascadedOperation:
#     def __init__(self, operation_list: list[Operation]):
#         self.__operation_list = operation_list
#
#     def undo(self):
#         for op in self.__operation_list:
#             op.undo()
#
#     def redo(self):
#         for op in reversed(self.__operation_list):
#             op.redo()



class UndoRedoException(Exception):
    pass


class UndoService:
    def __init__(self):
        self.__undo_stack = []
        self.__redo_stack = []
        self.__is_undoredo_op = False

    def record_for_undo(self, operation: Operation):
        if self.__is_undoredo_op:
            return
        print('Recorded operation for undo/redo.')
        self.__undo_stack.append(operation)
        self.__redo_stack = []

    def undo(self):
        print('Trying to undo..')
        if len(self.__undo_stack) == 0:
            raise UndoRedoException("No more undos")
        self.__is_undoredo_op = True
        operation = self.__undo_stack.pop()
        operation.undo()
        self.__redo_stack.append(operation)
        self.__is_undoredo_op = False

    def redo(self):
        print('Trying to redo...')
        if len(self.__redo_stack) == 0:
            raise UndoRedoException("No more redo")
        self.__is_undoredo_op = True
        operation = self.__redo_stack.pop()
        operation.redo()
        self.__undo_stack.append(operation)
        self.__is_undoredo_op = False

    def __str__(self):
        print('Undos and redos:')

        op_str = 'UNDO stack\n'
        for nr_op, op in enumerate(self.__undo_stack):
            op_str += str(nr_op) + " "
            op_str += str(op)
            op_str += '\n'
        op_str += 'REDO stack\n'

        for nr_op, op in enumerate(self.__redo_stack):
            op_str += str(nr_op) + " "
            op_str += str(op)
            op_str += '\n'
        return op_str
