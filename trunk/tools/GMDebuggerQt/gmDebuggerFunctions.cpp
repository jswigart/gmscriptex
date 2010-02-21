#include "gmdebuggerqt.h"

void GMDebuggerQt::gmDebuggerBreak(int a_threadId, int a_sourceId, int a_lineNumber)
{
	gmMachineGetContext(a_threadId, 0);
}

void GMDebuggerQt::gmDebuggerRun(int a_threadId, int a_lineNum, const char *a_func, const char *a_file)
{
	if(!a_file || !a_file[0])
		a_file = "<unknownfile>";
	if(!a_func || !a_func[0])
		a_func = "<unknownfunc>";

	AddUniqueThread( a_threadId, "Running", a_func, a_file );
}

void GMDebuggerQt::gmDebuggerStop(int a_threadId)
{
	RemoveThread(a_threadId);
}

void GMDebuggerQt::gmDebuggerSource(int a_sourceId, const char * a_sourceName, const char * a_source)
{
	SourceInfo info;
	info.sourceFile = a_sourceName;
	info.sourceData = a_source;
	sourceMap.insert(a_sourceId,info);

	if ( currentSourceId == a_sourceId ) {
		ui.scriptEdit->setPlainText(a_source);
		ui.scriptEdit->setDocumentTitle(a_sourceName);
	}
}

void GMDebuggerQt::gmDebuggerException(int a_threadId)
{
	gmMachineGetContext(a_threadId, 0);
}

void GMDebuggerQt::gmDebuggerBeginContext(int a_threadId, int a_callFrame)
{
	while(ui.callStack->rowCount())
		ui.callStack->removeRow(0);
	//ui.callStack->clear();
	while(ui.context->rowCount())
		ui.context->removeRow(0);
	//ui.context->clear();
	/*GMDebuggerFrame *pApp = static_cast<GMDebuggerFrame*>(a_session->m_user);
	pApp->m_currentDebugThread = a_threadId;
	pApp->FindAddThread(a_threadId, 4, true);
	pApp->ClearCallstack();
	pApp->BeginContext(0);*/
	currentThreadId = a_threadId;
	currentCallFrame = a_callFrame;
}

void GMDebuggerQt::gmDebuggerContextCallFrame(int a_callFrame, const char * a_functionName, int a_sourceId, int a_lineNumber, const char * a_thisSymbol, const char * a_thisValue, const char * a_thisType, int a_thisId)
{
	// add the var to the callstack
	{
		QString str;
		str.sprintf( "%s (%d)", a_functionName, a_lineNumber );
		const int newRow = ui.callStack->rowCount();
		ui.callStack->insertRow( newRow );
		ui.callStack->setItem( newRow, Callstack_FuncName, new QTableWidgetItem(str) );
	}

	currentSourceId = a_sourceId;

	// Update the call stack.
	if(currentCallFrame == a_callFrame)
	{
		{
			const int newRow = ui.context->rowCount();
			ui.context->insertRow( newRow );
			ui.context->setItem( newRow, Context_Name, new QTableWidgetItem( a_thisSymbol ) );
			ui.context->setItem( newRow, Context_Type, new QTableWidgetItem( a_thisType ) );
			ui.context->setItem( newRow, Context_Value, new QTableWidgetItem( a_thisValue ) );
		}

		// do we have the source code?
		//pApp->m_lineNumberOnSourceRcv = -1;
		QMap<int,SourceInfo>::iterator it = sourceMap.find( a_sourceId );
		if ( it == sourceMap.end() ) {
			gmMachineGetSource( a_sourceId );
			//pApp->m_lineNumberOnSourceRcv = a_lineNumber;
		} else {
			ui.scriptEdit->setPlainText( it.value().sourceData );
			ui.scriptEdit->setDocumentTitle( it.value().sourceFile );
			ui.scriptEdit->SetLineSelected( a_lineNumber );
		}
	}
}

void GMDebuggerQt::gmDebuggerContextVariable(const char * a_varSymbol, const char * a_varValue, const char * a_varType, int a_varId)
{
	const int newRow = ui.context->rowCount();
	ui.context->insertRow( newRow );
	ui.context->setItem( newRow, Context_Name, new QTableWidgetItem( a_varSymbol ) );
	ui.context->setItem( newRow, Context_Type, new QTableWidgetItem( a_varType ) );
	ui.context->setItem( newRow, Context_Value, new QTableWidgetItem( a_varValue ) );
}

void GMDebuggerQt::gmDebuggerEndContext()
{
	//GMDebuggerFrame *pApp = static_cast<GMDebuggerFrame*>(a_session->m_user);
	//pApp->EndContext();
}

void GMDebuggerQt::gmDebuggerBeginThreadInfo()
{
	ui.threadTable->clear();
	threadRowMap.clear();
}

void GMDebuggerQt::gmDebuggerThreadInfo(int a_threadId, const char * a_threadState, int a_lineNum, const char * a_func, const char * a_file)
{
	AddUniqueThread( a_threadId, a_threadState, a_func, a_file );
}

void GMDebuggerQt::gmDebuggerEndThreadInfo()
{
	//ui.threadTable->sortItems(0);
}

void GMDebuggerQt::gmDebuggerError(const char * a_error)
{
	ui.outputWindow->append( a_error );
}

void GMDebuggerQt::gmDebuggerMessage(const char * a_message)
{
	ui.outputWindow->append( a_message );
}

void GMDebuggerQt::gmDebuggerBreakPointSet(int a_sourceId, int a_lineNum)
{
	// todo:
}

void GMDebuggerQt::gmDebuggerQuit()
{
	//GMDebuggerNet::Disconnect();
}

//////////////////////////////////////////////////////////////////////////

void GMDebuggerQt::gmDebuggerBeginGlobals(int a_varId)
{
	if ( a_varId ) {
		VarItemMap::iterator it = varIdTreeMap.find( a_varId );
		if( it != varIdTreeMap.end() ) {
			parentCurrent = *it;
		}
	} else {
		parentCurrent = parentGlobals;
	}
}

void GMDebuggerQt::gmDebuggerGlobal(const char * a_varSymbol, 
									const char * a_varValue,
									const char * a_varType,
									int a_varId)
{
	if ( !parentCurrent ) {
		return;
	}

	// find parent to put under
	QTreeWidgetItem *newItem = new QTreeWidgetItem( parentCurrent );
	newItem->setText(TreeColumn_Name, a_varSymbol);
	newItem->setText(TreeColumn_Type, a_varType);
	newItem->setText(TreeColumn_Value, a_varValue);
	//newItem->setData(0,0,QVariant(a_varId));

	varIdTreeMap.insert( a_varId, newItem );

	if(a_varId != 0)
		gmMachineGetGlobalsInfo(a_varId);
}

void GMDebuggerQt::gmDebuggerEndGlobals()
{
	/*GMDebuggerFrame *pApp = static_cast<GMDebuggerFrame*>(a_session->m_user);
	pApp->EndGlobals();*/
}

int GMDebuggerQt::AddUniqueThread( int a_threadId, const char * a_status, const char * a_func, const char * a_file )
{
	const int newRow = ui.threadTable->rowCount();
	threadRowMap.insert( a_threadId, newRow );

	ui.threadTable->insertRow( newRow );
	ui.threadTable->setItem(newRow,Thread_Id,new QTableWidgetItem(QString::number(a_threadId)));
	ui.threadTable->setItem(newRow,Thread_Status,new QTableWidgetItem(a_status));
	ui.threadTable->setItem(newRow,Thread_Function,new QTableWidgetItem(a_func));
	ui.threadTable->setItem(newRow,Thread_Script,new QTableWidgetItem(a_file));

	return newRow;
}

void GMDebuggerQt::RemoveThread( int a_threadId )
{
	QList<QTableWidgetItem *> items = ui.threadTable->findItems(QString::number(a_threadId),Qt::MatchExactly);
	if ( !items.empty() ) {
		ui.threadTable->removeRow( items[0]->row() );
		threadRowMap.remove( a_threadId );
	}
}

void GMDebuggerQt::RemoveExpiredThreads()
{
}

void GMDebuggerQt::ThreadSelectionChanged()
{
	QList<QTableWidgetItem *> selected = ui.threadTable->QTableWidget::selectedItems();
	for ( int i = 0; i < selected.size(); ++i ) {
		QTableWidgetItem *threadId = ui.threadTable->item(selected[i]->row(),Thread_Id);
		if ( threadId ) {
			currentThreadId = threadId->text().toInt();
			gmMachineGetContext(currentThreadId, 0);
		}
		break;
	}
}
