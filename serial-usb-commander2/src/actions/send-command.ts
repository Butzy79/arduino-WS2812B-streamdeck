import { action, KeyDownEvent, SingletonAction } from "@elgato/streamdeck";

@action({ UUID: "com.butzy79.serial-usb-commander2.send" })
export class SendSerialCommand extends SingletonAction<SerialSettings> {

	override async onKeyDown(ev: KeyDownEvent<SerialSettings>): Promise<void> {

		const command = ev.payload.settings.command ?? "ON";

		console.log("COMMAND:", command);

		await ev.action.showOk();
	}
}

type SerialSettings = {
	command?: string;
};